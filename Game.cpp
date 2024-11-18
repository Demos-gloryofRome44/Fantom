#include "Game.hpp"
#include <filesystem>
#include <vector>
#include <string>
#include <filesystem>
#include <iostream>

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
               gameMap({"assets/labs/tiles/wallLeft.png", "assets/labs/tiles/wallCentr.png", "assets/labs/tiles/wallRight.png",
               "assets/labs/tiles/left.png", "assets/labs/tiles/right.png", "assets/labs/tiles/block.png", 
               "assets/labs/tiles/box.png"},
               {
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, // Стены по верхнему краю
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Открытое пространство с дверью
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Блоки и открытое пространство
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Открытое пространство и дверь
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Стены снизу
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Открытое пространство с дверью
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Блоки и двери
                   {3, -1, -1,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, // Открытое пространство с дверями
                   {3, -1,  6,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }),
               player(loadTexturesFromDirectory("assets/entity/Walking"), 200.f, 150.f, 
               window.getSize().x,
               window.getSize().y),
               movingUp(false), movingDown(false), movingLeft(false), movingRight(false) {}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();

        window.clear();
        gameMap.draw(window);
        player.draw(window);
        window.display();
    }
}

void Game::processEvents() {
    //window.setKeyboardFocus(true);
    window.setActive(true); // Установка фокуса н

    if (right == false) {
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
        std::cout << "Moving up" << std::endl; 
        player.move(0.f, -speed, gameMap);
    }
    if (movingDown) {
        std::cout << "Moving down" << std::endl; 
        player.move(0.f, speed, gameMap);
    }
    if (movingLeft) {
        std::cout << "Moving left" << std::endl;
        player.updateSprite(true);
        player.move(-speed, 0.f, gameMap);
    }
    if (movingRight) {
        std::cout << "Moving right" << std::endl; 
        player.updateSprite(false);
        player.move(speed, 0.f, gameMap);
    }

    gameMap.updateEnemies(deltaTime, player);
    player.update(deltaTime);
}
