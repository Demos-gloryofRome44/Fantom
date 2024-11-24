#include "Game.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>
#include "Menu.hpp"

// Функция для загрузки текстур из директории
std::vector<std::string> loadTexturesFromDirectory(const std::string& directory) {
    std::vector<std::string> textureFiles;

    // Проверка существования директории
    if (!std::filesystem::exists(directory)) {
        std::cerr << "Директория не найдена: " << directory << std::endl;
        return textureFiles; // Возвращаем пустой вектор
    }
    // Проходим по всем файлам в директории
    for (const auto& entry : std::filesystem::directory_iterator(directory)) {
        if (entry.is_regular_file()) { // Проверяем, что это файл
            const std::string& path = entry.path().string();
            // Проверяем расширение файла (например, .png или .jpg)
            if (path.ends_with(".png") || path.ends_with(".jpg") || path.ends_with(".jpeg")) {
                textureFiles.push_back(path); // Добавляем путь к файлу в вектор
            }
        }
    }

    return textureFiles; // Возвращаем список загруженных текстур
}


Game::Game() : window(sf::VideoMode(512, 320), "Dark Entity Escape"),
               player(loadTexturesFromDirectory("assets/entity/Walking"), 
               loadTexturesFromDirectory("assets/entity/Dying"),
                32.f, 219.f, 
               window.getSize().x,
               window.getSize().y),
               movingUp(false), movingDown(false), movingLeft(false), movingRight(false) {

                std::unordered_map<int, std::string> textureFiles = {
        {0, "assets/labs/tiles/wallLeft.png"},
        {1, "assets/labs/tiles/wallCentr.png"},
        {2, "assets/labs/tiles/wallRight.png"},
        {3, "assets/labs/tiles/left.png"},
        {4, "assets/labs/tiles/right.png"},
        {5, "assets/labs/tiles/leftPlat.png"},
        {6, "assets/labs/tiles/Plat.png"},
        {7, "assets/labs/tiles/rightPlat.png"},
        {8, "assets/labs/tiles/box.png"},
        {9, "assets/labs/tiles/krest.png"},
        {10, "assets/labs/tiles/block.png"},
        {12, "assets/labs/tiles/leftRed.png"},
        {13, "assets/labs/tiles/red.png"},
        {14, "assets/labs/tiles/rightRed.png"},
        {15, "assets/labs/tiles/redLeft.png"},
        {16, "assets/labs/tiles/redWallLeft.png"},
        {17, "assets/labs/tiles/redWall.png"},
        {18, "assets/labs/tiles/redLeft.png"},

        {11, "assets/labs/animate/Entry.png"},
        {19, "assets/labs/animate/constDoor.png"},

        {20, "assets/labs/tiles/shaxt.png"},
        {21, "assets/labs/tiles/redBlock.png"},

        {22, "assets/labs/tilesTown/Tile_01.png"},
        {23, "assets/labs/tilesTown/Tile_02.png"},
        {24, "assets/labs/tilesTown/Tile_04.png"},
        {25, "assets/labs/tilesTown/Tile_10.png"},
        {26, "assets/labs/tilesTown/Tile_13.png"},
        {27, "assets/labs/tilesTown/Tile_24.png"},
        {28, "assets/labs/tilesTown/Tile_12.png"},



        {40, "assets/labs/tiles/stolb.png"},
        {41, "assets/labs/tiles/stolb1.png"},
        {42,"assets/labs/Objects/locker.png"},
        {43,"assets/labs/Objects/Box1.png"},
        {44,"assets/labs/Objects/Box2.png"},
        {45,"assets/labs/Objects/Box8.png"},
        {46, "assets/labs/tiles/stolbRed.png"},

        {47, "assets/labs/Objects/locker1.png"},
        {48, "assets/labs/Objects/locker2.png"},
        {49, "assets/labs/Objects/locker3.png"},
        {51, "assets/labs/Objects/pointer1.png"},
        {52, "assets/labs/Objects/barrel1.png"},
        {53, "assets/labs/Objects/barrel2.png"},
        {54, "assets/labs/Objects/barrel3.png"},
        {55, "assets/labs/Objects/board1.png"},
        {56, "assets/labs/Objects/board2.png"},
        {57, "assets/labs/Objects/flag.png"},
        {58, "assets/labs/Objects/fence1.png"},
        {59, "assets/labs/Objects/fence2.png"},
        {60, "assets/labs/Objects/fence3.png"},

        {61, "assets/labs/outObjects/trees/3.png"},
        {62, "assets/labs/outObjects/other/Pointer1.png"},
        {63, "assets/labs/outObjects/Stones/6.png"},
        {64, "assets/labs/outObjects/Grass/16.png"},
        {65, "assets/labs/tiles/white.png"},

        {50, "assets/labs/animate/Screen2.png"},

        {100, "assets/labs/diamond.png"}
    };

                // 1-уровень
                maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {3, -1, -1, -1, -1, -1, -1, 41, -1, -1, 41, -1, -1, -1, -1, 11}, 
                   {3, 43, -1, -1, -1, -1, -1, 40, -1,100, 40, -1, -1, -1, -1, 39}, 
                   {3,  6, -1, -1, -1, -1, -1,  9,  9,  9,  9, -1, -1,  5,  6, 7}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1,  8, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, 42, 4}, 
                   {3, -1,  8,  8, -1, 10, 50, -1, -1, -1, -1, -1, -1, -1, 42, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
                }
                );

               // 2-уровень
               maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   { 0,  1,  1,  1,  1, 16,  1,  1, 16, 17, 17, 17, 17,  1,  1,  1, 2}, 
                   {19, -1, -1, -1, -1, 21, -1, 57, 15, -1, -1, -1, -1,  -1, -1, 4}, 
                   {39, -1, -1, -1, -1, 21,100, -1, 15, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3, -1, -1, -1, -1, 12, 21, -1, 15, -1, 50, -1, -1, -1, -1, 4}, 
                   { 3, -1, -1, -1, -1, -1, -1, -1, 12, 13, 13, 13, 14, -1, -1, 4}, 
                   { 3, -1, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 41, -1, -1, 4}, 
                   { 3, 45, -1, -1, -1, -1, -1, -1, 41, -1, -1, -1, 41, -1, -1, 11}, 
                   { 3, 42, 48, 47, -1, -1, -1, -1, 41, -1, -1, -1, 41, -1, -1, 39}, 
                   { 3, 42,  8, 49, -1, -1, -1, 51, 40, -1, 45, -1, 41, -1, -1, 4},
                   { 6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );

               // 3-уровень
               maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   { 0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   { 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3, -1, -1, -1, 43, 44, -1, -1, -1, -1, -1, 52, 28, 53, 54, 4}, 
                   { 3, 13, -1, 16, 17, 17, -1, -1, -1, -1, 28, 28, 28, 28, 28, 4}, 
                   { 3, -1, -1, 21, -1, -1, -1, -1, -1, -1, 28, -1, -1, -1, -1, 4}, 
                   {19, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {39, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3,  9, 20, 21, 56, 55, -1, -1, -1, -1, -1, -1, -1, 20, -1, 11}, 
                   { 3, 20,  9,  6, 50, 43, -1, -1, -1, -1, -1,  8, 20, 20, -1, 39},
                   { 6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );

               // 4-уровень
               maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   { 0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   { 3, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   { 3, -1, -1, 46, 43, 44, -1, 46, 58, 59, 60, -1, -1, -1, 50, 8}, 
                   { 3, 13, -1, 46, 13, 13, 13, 46,  9,  9, 13, -1, -1, 13, 13, 8}, 
                   { 3, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   {19, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, 57, 8}, 
                   {39, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   { 3,  9, 20, 46, 56, 55, -1, 46, -1, -1, -1, -1, -1, -1, -1, 11}, 
                   { 3, 20,  9, 46, 43, 43, -1, 46, -1, 52, 45, 45, 45, -1, -1, 39},
                   { 6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );

               // 5-уровень
               maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   {22, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 23, 24}, 
                   {25, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26}, 
                   {25, -1, -1, 65, 43, 44, -1, -1, -1, -1, 28, -1, -1, 64, -1, 26}, 
                   {25, 13, -1, 65, 28, 28, 28, -1,  9,  9, 13, -1, -1, 13, 13, 26}, 
                   {25, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26}, 
                   {19, -1, -1, 65, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 57, 26}, 
                   {39, -1, -1, 65, -1, -1, 61, -1, -1, -1, -1, -1, 61, -1, -1, 26}, 
                   {25,  9, 28, 65, 56, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11}, 
                   {25, 28,  9, 65, 64, 64, -1, -1, -1, 50, 62, 63, -1, -1, -1, 39},
                   {27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27, 27}
               }
               );


    // Инициализация фона полоски энергии
    energyBarBackground.setSize(sf::Vector2f(80.f, 10.f));
    energyBarBackground.setFillColor(sf::Color(50, 50, 50)); 
    energyBarBackground.setPosition(10.f, 10.f); // Позиция в левом верхнем углу

    // Инициализация самой полоски энергии
    energyBar.setSize(sf::Vector2f(80.f, 10.f)); // Размер полоски
    energyBar.setFillColor(sf::Color(128, 0, 128)); 
    energyBar.setPosition(10.f, 10.f); // Позиция такая же, как у фона

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
            if (result == 2) { // Если выбрана опция выхода
                isGameOver = true;
                return;
            }
            isGameOver = false;
            return;
        }
        processEvents();
        if (isGameOver == true) { return;}
        update();

        window.clear();
        maps[currentMapIndex].draw(window);
        player.draw(window);

        window.draw(energyBarBackground); // Отрисовка фона полоски энергии
        window.draw(energyBar);
        
        if (player.showMessage) {
            window.draw(player.messageText); // Отрисовка текстового сообщения
        }
        

        for (auto& explosion : explosions) {
            explosion.draw(window); // Рисуем все взрывы
        }

        window.draw(timeText);

        window.display();
    }
}

void Game::processEvents() {
    //window.setKeyboardFocus(true);
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
            if (event.key.code == sf::Keyboard::Space && lastExplosionTime >= explosionCooldown)  { // Проверка на пробел
                    triggerExplosion(player.getPosition()); // Вызываем взрыв на позиции игрока
                    std::cout << "tab pressed" << std::endl;
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

    if (movingUp && player.currentEnergy > 0) {
        player.move(0.f, -speed, maps[currentMapIndex]);

        player.currentEnergy -= player.energyConsumptionRate * deltaTime; // Уменьшаем энергию при движении вверх
        if (player.currentEnergy < 0) {
            player.currentEnergy = 0; // Ограничиваем минимальное значение энергии
        }
    }
    if (movingUp && player.currentEnergy == 0) {
        player.move(0.f, speed, maps[currentMapIndex]);
    }
    
    if ((movingDown || !player.isOnGround(maps[currentMapIndex])) && !movingUp) {
        player.move(0.f, speed, maps[currentMapIndex]);
        if (player.currentEnergy + player.energyRecoveryRate * deltaTime <= player.maxEnergy) {
            player.currentEnergy += player.energyRecoveryRate * deltaTime;
        }
    }

    if (movingLeft) {
        player.updateSprite(true);
        player.move(-speed, 0.f, maps[currentMapIndex]);
        turn = false;
    }
    if (movingRight) {
        player.updateSprite(false);
        player.move(speed, 0.f, maps[currentMapIndex]);
        turn = true;
    }

    float energyPercentage = player.currentEnergy / player.maxEnergy; // Процент оставшейся энергии
    energyBar.setSize(sf::Vector2f(80.f * energyPercentage, 10.f));

    player.update(deltaTime);
 
    if (player.end) {
        isGameOver = true; // Завершаем игру
    }

    for (auto it = explosions.begin(); it != explosions.end(); ) {
        it->update(deltaTime); // Обновляем анимацию взрыва

        if (it->isFinished()) { // Проверяем завершение анимации
            it = explosions.erase(it); // Удаляем завершенные взрывы
        } else {
            ++it; // Переходим к следующему взрыву
        }
    }

    maps[currentMapIndex].updateEnemies(deltaTime, player, explosions);
    maps[currentMapIndex].update(deltaTime);

    if (player.showMessage) {
        player.messageDisplayTime += deltaTime; // Увеличиваем время отображения

        if (player.messageDisplayTime >= 2.f) { // Если прошло больше 3 секунд
            player.showMessage = false; // Скрываем сообщение
            player.messageDisplayTime = 0.f; // Сбрасываем таймер
        }
    }

    if (maps[currentMapIndex].isExitTile(player.getPosition())) { 
        totalCrystel += maps[currentMapIndex].visitedCrystals.size();

        if (currentMapIndex == maps.size() - 1) { // Check if it's the last map
            Menu endmenu;
            endmenu.displayResults(window, totalTime, totalCrystel);
            return; // Exit update loop
        }
        currentMapIndex = (currentMapIndex + 1) % maps.size(); // Переход к следующей карте
        player.setPosition(50.f, 150.f); // Сброс позиции игрока в новой карте
        player.doorActivation = false;
    } 
}

void Game::restart() {
    player.setPosition(200.f, 150.f); // Вернуть игрока на начальную позицию

    player.resetState();

    maps[currentMapIndex].reset();                   // Предполагается, что у вас есть метод для сброса карты

    // Сброс флагов движения
    movingUp = false;
    movingDown = false;
    movingLeft = false;
    movingRight = false;

    // Сброс состояния окончания игры
    isGameOver = false;                // Устанавливаем флаг окончания игры в false
}

void Game::triggerExplosion(sf::Vector2f position) {
    if (turn) {
        explosions.emplace_back(position.x + 12, position.y + 12); // Создаем новый взрыв
    } else {
        explosions.emplace_back(position.x - 12, position.y + 12); // Создаем новый взрыв
    }
}