#include "include/Game.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include <fstream>
#include "include/Menu.hpp"
#include "include/ResourceLoader.hpp"

Game::Game() : window(sf::VideoMode(512, 320), "Dark Entity Escape"),
               player("assets/entity/Walking/1.png",  "assets/entity/Walking/11.png",
               loader.loadTexturesFromDirectory("assets/entity/Dying"),
                32.f, 219.f, 
               window.getSize().x,
               window.getSize().y),
               movingUp(false), movingDown(false), movingLeft(false), movingRight(false) {

    auto textureFiles = loader.loadTextures("resources/textures.txt");

    auto mapsData = loader.loadMapsFromFile("resources/levels.txt");

    int curentMap = 0;
    for (const auto& level : mapsData) {
        maps.emplace_back(textureFiles, level, curentMap);
        curentMap++;
    }

    // Инициализация фона полоски энергии
    energyBarBackground.setSize(sf::Vector2f(80.f, 10.f));
    energyBarBackground.setFillColor(sf::Color(50, 50, 50)); 
    energyBarBackground.setPosition(10.f, 10.f); 
    // Инициализация самой полоски энергии
    energyBar.setSize(sf::Vector2f(80.f, 10.f)); 
    energyBar.setFillColor(sf::Color(128, 0, 128)); 
    energyBar.setPosition(10.f, 10.f); 

    // инициализация таймера
    if (!font.loadFromFile("assets/DsStamper.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
    }

    // Настройка текста
    timeText.setFont(font);
    timeText.setCharacterSize(24); 
    timeText.setFillColor(sf::Color(128, 0, 128)); 
    timeText.setPosition(10.f, 22.f);
}

void Game::run() {
    while (window.isOpen()) {
        if (isGameOver == true) {
            Menu menu;
            int result = menu.restartMenu(window);
            if (result == 2) { 
                isGameOver = true;
                return;
            }
            isGameOver = false;
            return;
        }
        processEvents();
        if (isGameOver == true) { return;}

        update();

        draw();
    }
}

void Game::draw() {
    window.clear();
    maps[currentMapIndex].draw(window);
    player.draw(window);

    window.draw(energyBarBackground); // Отрисовка фона полоски энергии
    window.draw(energyBar);
    
    if (player.showMessage) {
        window.draw(player.messageText); // Отрисовка таймера
    }

    for (auto& explosion : explosions) {
        explosion.draw(window); // Рисуем все взрывы
    }

    window.draw(timeText);

    window.display();
}

void Game::processEvents() {
    window.setActive(true); 

    if (true) {
        std::cout << "Можно нажимать клавиши" << std::endl;
        right = true;
    }
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::W) movingUp = true;            
            if (event.key.code == sf::Keyboard::S) movingDown = true;
            if (event.key.code == sf::Keyboard::A) movingLeft = true;
            if (event.key.code == sf::Keyboard::D) movingRight = true;
            if (event.key.code == sf::Keyboard::Space && lastExplosionTime >= explosionCooldown)  {
                    triggerExplosion(player.getPosition()); // Вызываем взрыв на позиции игрока
                    lastExplosionTime = 0.0f;
            }
        }
        if (event.type == sf::Event::Closed) { isGameOver = true; }

        if (event.type == sf::Event::KeyReleased) {
            if (event.key.code == sf::Keyboard::W) movingUp = false;
            if (event.key.code == sf::Keyboard::S) movingDown = false;
            if (event.key.code == sf::Keyboard::A) movingLeft = false;
            if (event.key.code == sf::Keyboard::D) movingRight = false;
        }
    }
}


void Game::update() {
    float deltaTime = gameClock.restart().asSeconds(); // Получаем время с последнего кадра
    lastExplosionTime += deltaTime;
    totalTime += deltaTime;    
    timeText.setString(std::to_string(static_cast<int>(totalTime)));

    float mapWidth = 520.f; 
    float mapHeight = 320.f; 

    float scaleX = window.getSize().x / mapWidth; 
    float scaleY = window.getSize().y / mapHeight;

    // Подержание соотвествущей скорости, при расширени окна
    const float minScale = 0.8f; 
    const float maxScale = 1.4f; 

    // Ограничиваем значения масштаба
    scaleX = std::clamp(scaleX, minScale, maxScale);
    scaleY = std::clamp(scaleY, minScale, maxScale);

    if (player.isAlive){
        if (movingUp && player.currentEnergy > 0) {
            player.move(0.f, -speed * scaleY, maps[currentMapIndex]);

            player.currentEnergy -= player.energyConsumptionRate * deltaTime; // Уменьшаем энергию при движении вверх
            if (player.currentEnergy < 0) {
                player.currentEnergy = 0; 
            }
        }
        if (movingUp && player.currentEnergy == 0) {
            player.move(0.f, speed * scaleY, maps[currentMapIndex]);
        }
        
        if ((movingDown || !player.isOnGround(maps[currentMapIndex])) && !movingUp) {
            player.move(0.f, speed * scaleY, maps[currentMapIndex]);
            if (player.currentEnergy + player.energyRecoveryRate * deltaTime <= player.maxEnergy) {
                player.currentEnergy += player.energyRecoveryRate * deltaTime;
            }
        }

        if (movingLeft) {
            player.updateSprite(true);
            player.move(-speed * scaleX, 0.f, maps[currentMapIndex]);
            turn = false;
        }
        if (movingRight) {
            player.updateSprite(false);
            player.move(speed * scaleX, 0.f, maps[currentMapIndex]);
            turn = true;
        }
    }

    float energyPercentage = player.currentEnergy / player.maxEnergy; // Процент оставшейся энергии
    energyBar.setSize(sf::Vector2f(80.f * energyPercentage, 10.f));

    player.update(deltaTime);
 
    if (player.end) {
        isGameOver = true; 
    }

    for (auto it = explosions.begin(); it != explosions.end(); ) {
        it->update(deltaTime); // Обновляем анимацию взрыва

        if (it->isFinished()) { /
            it = explosions.erase(it); // Удаляем завершенные взрывы
        } else {
            ++it; // Переходим к следующему взрыву
        }
    }

    maps[currentMapIndex].updateEnemies(deltaTime, player, explosions);
    maps[currentMapIndex].update(deltaTime);

    if (player.showMessage) { // Сообщение о успешном сброе кристала 
        player.messageDisplayTime += deltaTime; 

        if (player.messageDisplayTime >= 2.f) { // Если прошло больше ~2 секунд
            player.showMessage = false; 
            player.messageDisplayTime = 0.f; 
        }
    }

    if (maps[currentMapIndex].isExitTile(player.getPosition())) { 
        totalCrystel += maps[currentMapIndex].visitedCrystals.size();

        if (currentMapIndex == maps.size() - 1) { 
            Menu endmenu;
            endmenu.displayResults(window, totalTime, totalCrystel);
            return; 
        }
        if (currentMapIndex == 6) {
            currentMapIndex = (currentMapIndex + 2) % maps.size(); // Переход к следующей карте
        } else { currentMapIndex = (currentMapIndex + 1) % maps.size(); }
        player.setPosition(50.f, 150.f); // Сброс позиции игрока в новой карте
        player.doorActivation = false;
    } 

    // метод для двери в которую можно войти несколько раз туда и обратно
    if (maps[currentMapIndex].isExitTileEnd(player.getPosition())) { 
        totalCrystel += maps[currentMapIndex].visitedCrystals.size();

        if (currentMapIndex == 6) {
            currentMapIndex = currentMapIndex + 1;
            player.setPosition(50.f, 150.f); 
        } else {
            currentMapIndex = currentMapIndex - 1;
            player.setPosition(450.f, 70.f); 
        }

        player.doorActivation = false;
    } 

}

void Game::triggerExplosion(sf::Vector2f position) {
    if (turn) {
        explosions.emplace_back(position.x + 12, position.y + 12); 
    } else {
        explosions.emplace_back(position.x - 12, position.y + 12); 
    }
}