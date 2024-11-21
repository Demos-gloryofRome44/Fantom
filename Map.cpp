#include "Map.hpp"

Map::Map(const std::vector<std::string>& textureFiles, const std::vector<std::vector<int>>& mapData) {
    for (size_t i = 0; i < textureFiles.size(); ++i) {
        sf::Texture texture;
        if (!texture.loadFromFile(textureFiles[i])) {
            std::cerr << "Ошибка загрузки текстуры из " << textureFiles[i] << std::endl;
        }
        textures.push_back(texture);
    }
    // Загрузка текстуры фона
    if (!backgroundTexture.loadFromFile("assets/labs/Background/Background.png")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }
    
    backgroundSprite.setTexture(backgroundTexture); 
    backgroundSprite.setPosition(0.f, 0.f);
    
    // Установка карты
    map = mapData;

    enemies.emplace_back("assets/enemy/Soldier_1/Walk.png", "assets/enemy/Soldier_1/Shot_2.png", 400.f, 219.f, 50.f, 50.f); 
}

// Метод для отрисовки карты
void Map::draw(sf::RenderWindow& window) {
    window.draw(backgroundSprite);

    for (size_t y = 0; y < map.size(); ++y) {
        for (size_t x = 0; x < map[y].size(); ++x) {
            int tileType = map[y][x];
            if (tileType == -1) {
                continue; // Игнорируем фон
            }
            if (tileType >= 0 && tileType < textures.size()) { // Проверка на допустимый тип тайла
                sf::Sprite sprite;
                sprite.setTexture(textures[tileType]);
                sprite.setPosition(x * tileSize, y * tileSize); 
                window.draw(sprite); 
            }
        }
    }

    for (auto& enemy : enemies) {
        enemy.draw(window);
    }
}

sf::FloatRect Map::getTileBounds(size_t x, size_t y) const {
    return sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
}

void Map::updateEnemies(float deltaTime, Entity &player) {
    for (auto& enemy : enemies) {
        enemy.update(deltaTime, *this, player); 
    }
}

void Map::reset() {
    map = {
                   {0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 2}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1, -1,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4}, 
                   {3, -1,  6,  6, -1,  1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 4},
                   {6,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5, 6}
    };
}