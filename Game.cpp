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



        {50, "assets/labs/animate/Screen2.png"}
    };

                // 1-уровень
                maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {3, -1, -1, -1, -1, -1, -1, 41, -1, -1, 41, -1, -1, -1, -1, 11}, 
                   {3, 43, -1, -1, -1, -1, -1, 40, -1, -1, 40, -1, -1, -1, -1, 39}, 
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
                   { 0,  1,  1,  1,  1,  1,  1,  1, 16, 17, 17, 17, 17,  1,  1,  1, 2}, 
                   {19, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1,  -1, -1, 4}, 
                   {39, -1, -1, -1, -1, -1, -1, -1, 15, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3, -1, -1, -1, -1, -1, -1, -1, 15, -1, 50, -1, -1, -1, -1, 4}, 
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
                   { 3, -1, -1, -1, 43, 44, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3, 13, -1, 16, 17, 17, -1, -1, -1, -1, -1, -1, -1,  4,  4, 4}, 
                   { 3, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {19, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {39, -1, -1, 21, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   { 3,  9, 20, 21, 56, 55, -1, -1, -1, -1, -1, -1, -1, -1, -1, 11}, 
                   { 3, 20,  9,  6, 50, 43, -1, -1, -1,  8, -1, -1, -1, -1, -1, 39},
                   { 6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
               }
               );

               // 4-уровень
               maps.emplace_back(textureFiles,
                    std::vector<std::vector<int>>{
                   { 0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   { 3, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   { 3, -1, -1, 46, 43, 44, -1, 46, 58, 59, 60, -1, -1, -1, -1, 8}, 
                   { 3, 13, -1, 46, 13, 13, 13, 46,  9,  9, 13, -1, -1, 13, 13, 8}, 
                   { 3, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   {19, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, 57, 8}, 
                   {39, -1, -1, 46, -1, -1, -1, 46, -1, -1, -1, -1, -1, -1, -1, 8}, 
                   { 3,  9, 20, 46, 56, 55, -1, 46, -1, -1, -1, -1, -1, -1, -1, 11}, 
                   { 3, 20,  9, 46, 43, 43, -1, 46, -1, 50, 45, 45, 45, -1, -1, 39},
                   { 6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
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

        for (auto& explosion : explosions) {
            explosion.draw(window); // Рисуем все взрывы
        }

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

    if (movingUp) {
        player.move(0.f, -speed, maps[currentMapIndex]);
    }
    if (movingDown) {
        player.move(0.f, speed, maps[currentMapIndex]);
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

    if (maps[currentMapIndex].isExitTile(player.getPosition())) { 
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