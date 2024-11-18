#include "Enemy.hpp"
#include "Map.hpp"
#include "Entity.hpp"
#include <iostream>

Enemy::Enemy(const std::string& textureFile, const std::string& attackTextureFile,
        float posX, float posY, float width, float height)
    : currentFrame(0), attackFrame(0), animationSpeed(0.2f), attackAnimationSpeed(0.2f), elapsedTime(0.f), attackElapsedTime(0.f),
      speed(25.f), lastShotTime(0.f), shootCooldown(1.f), movingRight(true) {
    
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Ошибка загрузки текстуры из " << textureFile << std::endl;
    } else {
        std::cout << "Враг загружен"<< std::endl;
    }

    if (!attackTexture.loadFromFile(attackTextureFile)) {
        std::cerr << "Ошибка загрузки текстуры атаки из " << attackTextureFile << std::endl;
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
        
        elapsedTime = 0.f; 
    }
}

void Enemy::attackAnimate(float deltaTime) {
    attackElapsedTime += deltaTime;

    if (attackFrame == 0) {
        sprite.setTexture(attackTexture); // Устанавливаем текстуру атаки
        sprite.setTextureRect(sf::IntRect(45, 64, 52, 66)); // Устанавливаем начальный кадр
    }

    if (attackElapsedTime >= attackAnimationSpeed) {
        attackFrame = (attackFrame + 1) % 4; 
            
        int frameWidth = 65 + 63; // Ширина одного кадра атаки (может отличаться от ширины движения)
        int frameHeight = 66; // Высота одного кадра
            
        sprite.setTexture(attackTexture);
        // Устанавливаем новый прямоугольник текстуры для текущего кадра атаки
         sprite.setTextureRect(sf::IntRect(45 + attackFrame * frameWidth, 64, 70, frameHeight)); 
            
        attackElapsedTime = 0.f; 
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

void Enemy::update(float deltaTime, const Map& map, const Entity &player) {

    if (canSeePlayer(player, map)) {
        if (flag){
        std::cout<<"противник видит игрока, останавливаемся и начинаем стрелять"<<std::endl;
        flag = false;
        }
        lastShotTime += deltaTime;
        if (lastShotTime >= shootCooldown) {
            shoot(player);
            lastShotTime = 0.f; // Сброс таймера
        }

        attackAnimate(deltaTime);
        attackFlag = true;
        sprite.setScale(movingRight ? 1.f : -1.f, 1.f);
    } else if (attackFlag){
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(50, 60, 35, 70)); 
        attackFlag = false;
    } else {

        animate(deltaTime);
        // Если не видит игрока, продолжаем движение
        float direction = movingRight ? speed * deltaTime : -speed * deltaTime;
        move(direction, 0.f, map); // Движение по оси X

        sprite.setScale(movingRight ? 1.f : -1.f, 1.f); // Поворот текстуры
    }

    for (size_t i = 0; i < bullets.size(); ) {
        bullets[i].update(deltaTime); // Обновляем пулю

        // Проверка на столкновение с тайлом
        size_t bulletX = static_cast<size_t>(bullets[i].getPosition().x / tileSize);
        size_t bulletY = static_cast<size_t>(bullets[i].getPosition().y / tileSize);
        
        int tileType = map.getTileType(bulletX, bulletY);
        
        if (tileType != -1) { // Если тайл не проходимый
            bullets.erase(bullets.begin() + i); // Удаляем пулю из вектора
        } else {
            ++i; // Переходим к следующей пуле только если не удалили текущую
        }
    }
}

void Enemy::draw(sf::RenderWindow& window) {
   window.draw(sprite);
    
   for (auto& bullet : bullets) {
       bullet.draw(window);
   }
}

void Enemy::shoot(const Entity& player) {
    if (movingRight){
        bullets.emplace_back(position.x + sprite.getGlobalBounds().width, position.y + 14,
   player.getPosition()); 
    } else {
        bullets.emplace_back(position.x - sprite.getGlobalBounds().width, position.y + 14,
   player.getPosition()); 
    }
}

bool Enemy::canSeePlayer(const Entity& player, const Map& map) {
    sf::Vector2f enemyPosition = sprite.getPosition();
    sf::Vector2f playerPosition = player.getPosition(); 

    // Вычисляем направление к игроку
    sf::Vector2f direction = playerPosition - enemyPosition;

    // Длина луча
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    
    // Нормализуем направление
    direction /= distance;

    // Проверяем, движется ли враг в сторону игрока
    if ((movingRight && direction.x < 0) || (!movingRight && direction.x > 0)) {
        return false; // Противник не движется в сторону игрока
    }

    // Проверяем наличие стены по пути к игроку
    for (float d = 0; d < distance; d += 1.0f) { // Шаг 1.0f можно настроить для большей точности
        size_t newX = static_cast<size_t>((enemyPosition.x + direction.x * d) / tileSize);
        size_t newY = static_cast<size_t>((enemyPosition.y + direction.y * d) / tileSize);

        int tileType = map.getTileType(newX, newY);
        if (tileType != -1) { // Если не проходимый тайл
            return false; // Есть стена между противником и игроком
        }
    }

    return true; // Противник видит игрока
}