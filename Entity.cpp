#include "Entity.hpp"
#include "Map.hpp"

Entity::Entity(const std::string& textureFile, float posX, float posY, float width, float height) {
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Ошибка загрузки текстуры из " << textureFile << std::endl;
    } else {
        sprite.setTexture(texture); 
    }

    sprite.setPosition(posX, posY); 

    sprite.setTextureRect(sf::IntRect(50, 15, 345, 300));

    float scaleX = width / (sprite.getLocalBounds().width * 18); 
    float scaleY = height / (sprite.getLocalBounds().height * 12);

    sprite.setScale(scaleX, scaleY);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    std::cout << "New Bounds: " << bounds.left << ", " << bounds.top 
              << ", " << bounds.width << ", " << bounds.height << std::endl;
}

void Entity::move(float x, float y, const Map &map) {
    sf::Vector2f currentPosition = sprite.getPosition();

    // Перемещение
    sprite.move(x, y);
    

    // Проверка на столкновение
    if (checkCollision(map)) {
        // Если произошло столкновение, возвращаемся к старому положению
        sprite.setPosition(currentPosition);
    }
}

bool Entity::checkCollision(const Map& map) {
    // Получаем границы игрока
    sf::FloatRect playerBounds = getBounds();

    // Проходим по всем тайлам карты
    for (size_t y = 0; y < map.getHeight(); ++y) {
        for (size_t x = 0; x < map.getWidth(); ++x) {
            int tileType = map.getTileType(x, y); // Получаем тип тайла
            
            if (tileType != -1) { // Проверяем типы блоков
                sf::FloatRect tileBounds = map.getTileBounds(x, y); // Получаем границы тайла
                
                if (playerBounds.intersects(tileBounds)) {
                    return true; // Столкновение обнаружено
                }
            }
        }
    }
    
    return false; // Столкновение не обнаружено
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}