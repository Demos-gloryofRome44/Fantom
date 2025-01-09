#include "include/Map.hpp"

Map::Map(const std::unordered_map<int, std::string>& textureFiles, const std::vector<std::vector<int>>& mapData, 
      int currentMap) {
    for (const auto& pair : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(pair.second)) { // Используем путь из unordered_map
            std::cerr << "Ошибка загрузки текстуры из " << pair.second << std::endl;
        }
        textures[pair.first] = texture; // Сохраняем текстуру по ключу
    }
    if (currentMap < 4) {
    if (!backgroundTexture.loadFromFile("assets/labs/Background/Background.png")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }
    } else {
        if (!backgroundTexture.loadFromFile("assets/labs/Background/6.jpg")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }
    }
    
    // Установка карты
    map = mapData;

    // Спецификация добавления врагов для каждой карты 
    if (currentMap == 6) {
        return;
    }
    if (currentMap == 8) {
         enemies.emplace_back("assets/enemy/Soldier_2/Walk.png", "assets/enemy/Soldier_2/Shot_1.png", 
        "assets/enemy/Soldier_1/Dead.png", 200.f, 123.f, 11.f, 0.5f, 10); 
        return;
    }
    enemies.emplace_back("assets/enemy/Soldier_1/Walk.png", "assets/enemy/Soldier_1/Shot_2.png", 
    "assets/enemy/Soldier_1/Dead.png", 390.f, 219.f, 25.f, 1.f, 14); 
    if (currentMap >= 4) {
        enemies.emplace_back("assets/enemy/Soldier_2/Walk.png", "assets/enemy/Soldier_2/Shot_2.png", 
        "assets/enemy/Soldier_2/Dead.png", 300.f, 219.f, 35.f, 0.8f, 22); 
    }
    if (currentMap == 7) {
        enemies.emplace_back("assets/enemy/Soldier_2/Walk.png", "assets/enemy/Soldier_2/Shot_2.png", 
        "assets/enemy/Soldier_2/Dead.png", 270.f, 219.f, 35.f, 0.8f, 22); 
        
        enemies.emplace_back("assets/enemy/Soldier_1/Walk.png", "assets/enemy/Soldier_1/Shot_2.png", 
        "assets/enemy/Soldier_1/Dead.png", 200.f, 219.f, 25.f, 1.f, 14); 

        enemies.emplace_back("assets/enemy/Soldier_2/Walk.png", "assets/enemy/Soldier_2/Shot_1.png", 
        "assets/enemy/Soldier_2/Dead.png", 440.f, 58.f, 25.f, 0.6f, 22); 
    }
}

// Метод для отрисовки карты
void Map::draw(sf::RenderWindow& window) {
    backgroundSprite.setTexture(backgroundTexture); 
    backgroundSprite.setPosition(0.f, 0.f);
    window.draw(backgroundSprite);

    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            int tileType = map[y][x];
            if (tileType == -1) {
                continue; // Игнорируем фон
            }
            if (textures.find(tileType) != textures.end() && tileType != 11 && tileType != 100 && tileType != 29) { 
                sf::Sprite sprite;
                sprite.setTexture(textures[tileType]); // Получаем текстуру по индексу
                sprite.setPosition(x * tileSize, y * tileSize); 
                window.draw(sprite); 
            }

            if (tileType == 11 || tileType == 29) { 
                sf::Sprite doorSprite;
                doorSprite.setTexture(textures[tileType]); 
                doorSprite.setTextureRect(sf::IntRect(32 * currentDoorFrame, 0, 32, 64)); // Устанавливаем текущий кадр анимации
                doorSprite.setPosition(x * tileSize, y * tileSize); 
                window.draw(doorSprite); // Рисуем дверь с анимацией
            }

            if (tileType == 100) {
                sf::Vector2f crystalPosition(x * tileSize, y * tileSize);
                if (std::find(visitedCrystals.begin(), visitedCrystals.end(), crystalPosition) == visitedCrystals.end()) { 
                    sf::Sprite crystal;
                    crystal.setTexture(textures[tileType]); 
                    crystal.setPosition(crystalPosition); 
                    window.draw(crystal);
                }
            }
        }
    }

    for (auto& enemy : enemies) {
        enemy.draw(window);
    }
}

bool Map::isExitTile(const sf::Vector2f& position) const {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 11) { 
                sf::FloatRect tileBounds = getTileBounds(x, y);
                sf::FloatRect back = getTileBounds(x, y - 1);

                if (tileBounds.contains(position) || back.contains(position)) {
                    return true; 
                }
            }
        }
    }
    
    return false; // Игрок не на тайле выхода
}

bool Map::isExitTileEnd(const sf::Vector2f& position) const {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 29) { 
                sf::FloatRect tileBounds = getTileBounds(x, y);
                sf::FloatRect back = getTileBounds(x, y - 1);

                if (tileBounds.contains(position) || back.contains(position)) {
                    return true; 
                }
            }
        }
    }
    
    return false; // Игрок не на тайле выхода
}

sf::FloatRect Map::getTileBounds(size_t x, size_t y) const {
    return sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
}

void Map::updateEnemies(float deltaTime, Entity &player, const std::vector<Explosion>& explosions) {
    for (auto& enemy : enemies) {
        enemy.update(deltaTime, *this, player, explosions); 
    }
}

void Map::update(float deltaTime) {
    sf::Sprite sprite;
    // Проверка состояния двери, на то был ли активирован терминал
    if (doorActivation) {
    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            int tileType = map[y][x];
            if (tileType == 11 || tileType == 29) { // Проверяем, является ли тайл дверью
                doorAnimationTime += deltaTime; 
                if (doorAnimationTime >= doorFrameDuration) {
                    currentDoorFrame++; // Переход к следующему кадру анимации
                    doorAnimationTime = 0.f; 
                }
                if (currentDoorFrame >= 5) { // Если конец анимации
                    currentDoorFrame = 4; // Устанавливаем последний кадр
                }
            } 
        }
    }
    }
}