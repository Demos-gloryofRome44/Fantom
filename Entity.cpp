#include "Entity.hpp"
#include "Map.hpp"

Entity::Entity(const std::vector<std::string>& textureFiles, const std::vector<std::string>& dieTexturesFile,
 float posX, float posY, float width, float height)
    : currentFrame(0), animationSpeed(0.1f), elapsedTime(0.f), deathAnimationSpeed(0.2f), 
    currentDeathFrame(0), deathElapsedTime(0.f) {
    
    for (const auto& file : textureFiles) {
        sf::Texture texture;
        if (!texture.loadFromFile(file)) {
            std::cerr << "Ошибка загрузки текстуры из " << file << std::endl;
        } else {
            textures.push_back(texture); // Добавляем текстуру в вектор
        }
    }

    for (const auto& file : dieTexturesFile) {
        sf::Texture dieTexture;
        if (!dieTexture.loadFromFile(file)) {
            std::cerr << "Ошибка загрузки текстуры из " << file << std::endl;
        } else {
            dieTextures.push_back(dieTexture); // Добавляем текстуру в вектор
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

void Entity::move(float x, float y, Map &map) {
    sf::Vector2f currentPosition = sprite.getPosition();

    sprite.move(x, y);

    // Проверка на столкновение
    if (checkCollision(map)) {
        // Если произошло столкновение, возвращаемся к старому положению
        sprite.setPosition(currentPosition);
    } else {
        // Обновляем анимацию только если нет столкновения
        update(0.1f); 
    }
}

void Entity::updateSprite(bool turn) {
    if (turn) {
        sprite.setScale(-abs(sprite.getScale().x), sprite.getScale().y); // Переворачиваем по оси X
    } else {
        sprite.setScale(abs(sprite.getScale().x), sprite.getScale().y); // Возвращаем нормальный масштаб
    }
}

bool Entity::checkCollision(Map& map) {
    // Получаем границы игрока
    sf::FloatRect playerBounds = getBounds();

    // Проходим по всем тайлам карты
    for (size_t y = 0; y < map.getHeight(); ++y) {
        for (size_t x = 0; x < map.getWidth(); ++x) {
            sf::FloatRect tileBounds = map.getTileBounds(x, y); // Получаем границы тайла

            int tileType = map.getTileType(x, y); // Получаем тип тайла

            if (tileType == 50) {                
                if (playerBounds.intersects(tileBounds)) {
                    doorActivation = true;
                    map.setDoorActivation(doorActivation);
                }
            }

            if (tileType == 11 && doorActivation) {
                sf::FloatRect back = map.getTileBounds(x, y - 1);
                if (playerBounds.intersects(tileBounds)) {
                    return false; // Столкновение обнаружено
                }
                if (playerBounds.intersects(back)) {
                    return false; // Столкновение обнаружено
                }
            }
            
            if (tileType != -1 && tileType < 40) { // Проверяем типы блоков                
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
    if (!isAlive) {
        // Если мертв, обновляем анимацию смерти
        deathElapsedTime += deltaTime;

        if (deathElapsedTime >= deathAnimationSpeed) {
            if (currentDeathFrame == 0) {
                currentDeathFrame = 1;
                sprite.setTexture(dieTextures[currentDeathFrame]); // Устанавливаем первую текстуру смерти
                sprite.setTextureRect(sf::IntRect(135, 30, 220, 290));
            }
            else {
            currentDeathFrame = (currentDeathFrame + 1) % dieTextures.size(); // Переход к следующему кадру
            sprite.setTexture(dieTextures[currentDeathFrame]); // Устанавливаем новую текстуру для анимации смерти
            
            // Устанавливаем новый прямоугольник текстуры

            deathElapsedTime = 0.f; // Сбрасываем время
            }
        }

        if (currentDeathFrame == dieTextures.size() - 1) {
            std::cout << "Анимация смерти завершена." << std::endl;
            end = true;
            return;
        }
        
    } else {
        elapsedTime += deltaTime;

        if (elapsedTime >= animationSpeed) {
            currentFrame = (currentFrame + 1) % textures.size(); // Переход к следующему кадру
            sprite.setTexture(textures[currentFrame]); // Устанавливаем новую текстуру
        }
        elapsedTime = 0.f; // Сбрасываем время
    }
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition(); 
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y); // Устанавливаем позицию спрайта
}

void Entity::die() {
    if (!isAlive) return; // Если уже мертв, ничего не делаем

    isAlive = false; // Устанавливаем состояние мертвым

    std::cout << "Игрок умер!" << std::endl;
}

void Entity::resetState() {
    isAlive = true;                     // Устанавливаем состояние живым
    currentFrame = 0;                   // Сбрасываем текущий кадр анимации
    elapsedTime = 0.f;                  // Сбрасываем время анимации
    currentDeathFrame = 0;              // Сбрасываем текущий кадр анимации смерти
    deathElapsedTime = 0.f;              // Сбрасываем время анимации смерти
}