#include "Map.hpp"

Map::Map(const std::unordered_map<int, std::string>& textureFiles, const std::vector<std::vector<int>>& mapData) {
    for (const auto& pair : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(pair.second)) { // Используем путь из unordered_map
            std::cerr << "Ошибка загрузки текстуры из " << pair.second << std::endl;
        }
        textures[pair.first] = texture; // Сохраняем текстуру по ключу
    }
    // Загрузка текстуры фона
    if (!backgroundTexture.loadFromFile("assets/labs/Background/Background.png")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }
    
    // Установка карты
    map = mapData;

    enemies.emplace_back("assets/enemy/Soldier_1/Walk.png", "assets/enemy/Soldier_1/Shot_2.png", 
    "assets/enemy/Soldier_1/Dead.png", 400.f, 219.f, 50.f, 50.f); 
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
            if (textures.find(tileType) != textures.end()) { // Проверка на наличие текстуры по индексу
                sf::Sprite sprite;
                sprite.setTexture(textures[tileType]); // Получаем текстуру по индексу
                sprite.setPosition(x * tileSize, y * tileSize); 
                window.draw(sprite); 
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
            if (map[y][x] == 4) { 
                sf::FloatRect tileBounds = getTileBounds(x, y);
                if (tileBounds.contains(position)) {
                    return true; // Игрок находится на тайле выхода
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