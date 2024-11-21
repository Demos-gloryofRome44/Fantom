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
                200.f, 150.f, 
               window.getSize().x,
               window.getSize().y),
               movingUp(false), movingDown(false), movingLeft(false), movingRight(false) {
                maps.emplace_back(
                    std::vector<std::string>{"assets/labs/tiles/wallLeft.png", "assets/labs/tiles/wallCentr.png", 
                    "assets/labs/tiles/wallRight.png", "assets/labs/tiles/left.png", 
                    "assets/labs/tiles/right.png", "assets/labs/tiles/block.png", 
                    "assets/labs/tiles/box.png", "assets/labs/tiles/box.png",
                    "assets/labs/tiles/leftPlat.png", "assets/labs/tiles/plat.png", "assets/labs/tiles/rightPlat.png",
                    "assets/labs/tiles/krest.png", "assets/labs/tiles/stolb.png", "assets/labs/tiles/stolb1.png",
                    "assets/labs/Objects/locker.png", "assets/labs/Objects/Box1.png"
                    }, 
                    std::vector<std::vector<int>>{
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {3, -1, -1, -1, -1, -1, -1, 13, -1, -1, 13, -1, -1, -1, -1, -1}, 
                   {3, 15, -1, -1, -1, -1, -1, 12, -1, -1, 12, -1, -1, -1, -1, -1}, 
                   {3,  6, -1, -1, -1, -1, -1, 11, 11, 11, 11, -1, -1,  8,  9, 10}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, 14, 4}, 
                   {3, -1,  6,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, 14, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
                );

               maps.emplace_back(
                    std::vector<std::string>{"assets/labs/tiles/wallLeft.png", "assets/labs/tiles/wallCentr.png", "assets/labs/tiles/wallRight.png",
               "assets/labs/tiles/left.png", "assets/labs/tiles/right.png", "assets/labs/tiles/block.png", 
               "assets/labs/tiles/box.png"}, 
                    std::vector<std::vector<int>>{
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
                   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1,  6,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );

               maps.emplace_back(
                    std::vector<std::string>{"assets/labs/tiles/wallLeft.png", "assets/labs/tiles/wallCentr.png", "assets/labs/tiles/wallRight.png",
               "assets/labs/tiles/left.png", "assets/labs/tiles/right.png", "assets/labs/tiles/block.png", 
               "assets/labs/tiles/box.png"}, 
                    std::vector<std::vector<int>>{
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1,  6,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );
}

bool Game::run() {
    while (window.isOpen()) {
        if (isGameOver == true) {
            Menu menu;
            int result = menu.restartMenu(window);
            if (result == 2) { // Если выбрана опция выхода
                return false;
            }
            restart();
        }
        processEvents();
        update();

        if (player.getPosition().x > window.getSize().x) { // Если игрок выходит за пределы окна справа
            currentMapIndex = (currentMapIndex + 1) % maps.size(); // Переход к следующей карте
            player.setPosition(50.f, 50.f); // Сброс позиции игрока в новой карте
        }

        window.clear();
        maps[currentMapIndex].draw(window);
        player.draw(window);
        window.display();
    }
    return true;
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
            if (event.key.code == sf::Keyboard::W) { 
                movingUp = true;
                std::cout << "W pressed" << std::endl;
            }
            if (event.key.code == sf::Keyboard::S) movingDown = true;
            if (event.key.code == sf::Keyboard::A) movingLeft = true;
            if (event.key.code == sf::Keyboard::D) movingRight = true;
        }

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

    if (movingUp) {
        player.move(0.f, -speed, maps[currentMapIndex]);
    }
    if (movingDown) {
        player.move(0.f, speed, maps[currentMapIndex]);
    }
    if (movingLeft) {
        player.updateSprite(true);
        player.move(-speed, 0.f, maps[currentMapIndex]);
    }
    if (movingRight) {
        player.updateSprite(false);
        player.move(speed, 0.f, maps[currentMapIndex]);
    }

    player.update(deltaTime);

    if (player.end) {
        isGameOver = true; // Завершаем игру
    }

    maps[currentMapIndex].updateEnemies(deltaTime, player);

    if (maps[currentMapIndex].isExitTile(player.getPosition())) { 
        currentMapIndex = (currentMapIndex + 1) % maps.size(); // Переход к следующей карте
        player.setPosition(50.f, 150.f); // Сброс позиции игрока в новой карте
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