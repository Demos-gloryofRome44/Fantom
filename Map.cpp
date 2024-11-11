#include "Map.hpp"

// Конструктор, который загружает текстуры и устанавливает карту
Map::Map(const std::vector<std::string>& textureFiles, const std::vector<std::vector<int>>& mapData) {
    // Загрузка текстур
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
    
    backgroundSprite.setTexture(backgroundTexture); // Установка текстуры для спрайта
    backgroundSprite.setPosition(0.f, 0.f);
    
    // Установка карты
    map = mapData;
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
                sprite.setPosition(x * tileSize, y * tileSize); // Установка позиции спрайта
                window.draw(sprite); // Отрисовка спрайта
            }
        }
    }
}

sf::FloatRect Map::getTileBounds(size_t x, size_t y) const {
    return sf::FloatRect(x * tileSize, y * tileSize, tileSize, tileSize);
}