#include "Entity.hpp"
#include "Map.hpp"

Entity::Entity(const std::vector<std::string>& textureFiles, float posX, float posY, float width, float height)
    : currentFrame(0), animationSpeed(0.1f), elapsedTime(0.f) {
    
    for (const auto& file : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
            std::cerr << "Ошибка загрузки текстуры из " << file << std::endl;
        } else {
            textures.push_back(texture); // Добавляем текстуру в вектор
        }
    }
    sprite.setTexture(textures[currentFrame]); // Устанавливаем первую текстуру

    sprite.setPosition(posX, posY); 

    sprite.setTextureRect(sf::IntRect(135, 30, 220, 290));

    float scaleX = width / (sprite.getLocalBounds().width * 20); 
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
    } else {
        // Обновляем анимацию только если нет столкновения
        update(0.1f); // Здесь передайте время с последнего обновления (deltaTime)
    }
}

void Entity::updateSprite(bool turn) {
        if (turn) {
            sprite.setScale(-abs(sprite.getScale().x), sprite.getScale().y); // Переворачиваем по оси X
        } else {
            sprite.setScale(abs(sprite.getScale().x), sprite.getScale().y); // Возвращаем нормальный масштаб
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

void Entity::update(float deltaTime) {
    elapsedTime += deltaTime;

    if (elapsedTime >= animationSpeed) {
        currentFrame = (currentFrame + 1) % textures.size(); // Переход к следующему кадру
        sprite.setTexture(textures[currentFrame]); // Устанавливаем новую текстуру
        elapsedTime = 0.f; // Сбрасываем время
    }
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition(); 
}