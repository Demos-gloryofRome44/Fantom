#include "Enemy.hpp"
#include "Map.hpp"
#include <iostream>

Enemy::Enemy(const std::string& textureFile, float posX, float posY, float width, float height)
    : currentFrame(0), animationSpeed(0.2f), elapsedTime(0.f), speed(25.f), lastShotTime(0.f), shootCooldown(1.f),
     movingRight(true) {
    
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Ошибка загрузки текстуры из " << textureFile << std::endl;
    } else {
        std::cout << "Враг загружен"<< std::endl;
    }

    sprite.setTexture(texture); // Устанавливаем текстуру

    position = sf::Vector2f(posX, posY); // Инициализируем позицию врага
    sprite.setPosition(position); 

    // Установка начального прямоугольника текстуры (например, первый кадр)
    sprite.setTextureRect(sf::IntRect(50, 60, 35, 70)); 
}

void Enemy::animate(float deltaTime) {
    elapsedTime += deltaTime;

    if (elapsedTime >= animationSpeed) {
        currentFrame = (currentFrame + 1) % 7; 
        int frameWidth = 95 + 35; // Ширина одного кадра
        int frameHeight = 70; // Высота одного кадра
        
        // Устанавливаем новый прямоугольник текстуры для текущего кадра
        sprite.setTextureRect(sf::IntRect(30 + currentFrame * frameWidth, 60, 50, frameHeight));
        
        elapsedTime = 0.f; // Сбрасываем таймер
    }
}

void Enemy::move(float deltaX, float deltaY, const Map& map) {
    size_t newX;
    if (movingRight) {
        newX = static_cast<size_t>(((position.x + deltaX + 35.f) / tileSize));
    } else {
        newX = static_cast<size_t>(((position.x + deltaX - 35.f) / tileSize));
    }

    size_t newY = static_cast<size_t>((position.y + deltaY + 10.f) / tileSize);

    // Проверка типа тайла
    int tileType = map.getTileType(newX, newY);
    
    if (tileType == -1) { // Если тайл с весом 1
        position.x += deltaX;
        position.y += deltaY;
        sprite.setPosition(position); // Обновляем позицию спрайта
    } else {
        // Если столкнулись со стеной, меняем направление движения
        movingRight = !movingRight; 
    }
}

void Enemy::update(float deltaTime, const Map& map) {
    animate(deltaTime);

    float direction = movingRight ? speed * deltaTime : -speed * deltaTime;
    move(direction, 0.f, map); // Движение по прямой (например вправо)
    sprite.setScale(movingRight ? 1.f : -1.f, 1.f);

    lastShotTime += deltaTime;
    if (lastShotTime >= shootCooldown) {
        shoot();
        lastShotTime = 0.f; // Сброс таймера
    }

    for (auto& bullet : bullets) {
        bullet.update(deltaTime);
    }
}

void Enemy::draw(sf::RenderWindow& window) {
   window.draw(sprite);
    
   for (auto& bullet : bullets) {
       bullet.draw(window);
   }
}

void Enemy::shoot() {
   bullets.emplace_back(position.x + sprite.getGlobalBounds().width, position.y + sprite.getGlobalBounds().height / 2, 300.f); // Создаем пулю
}