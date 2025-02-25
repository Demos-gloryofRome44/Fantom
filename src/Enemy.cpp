#include "include/Enemy.hpp"
#include "include/Map.hpp"
#include "include/Entity.hpp"
#include <iostream>
#include <cmath>

Enemy::Enemy(const std::string& textureFile, const std::string& attackTextureFile, const std::string& deathTextureFile,
        float posX, float posY, float speedEnemy, float rechargeTime, int yShootEnemy)
    : currentFrame(0), attackFrame(0), deathFrame(0), animationSpeed(0.2f), attackAnimationSpeed(0.2f), deathAnimationSpeed(0.3f),
    elapsedTime(0.f), attackElapsedTime(0.f), deathElapsedTime(0.f), yShoot(yShootEnemy),
      speed(speedEnemy), lastShotTime(0.f), shootCooldown(rechargeTime), movingRight(false) {
    
    if (!texture.loadFromFile(textureFile)) {
        std::cerr << "Ошибка загрузки текстуры из " << textureFile << std::endl;
    } else {
        std::cout << "Враг загружен"<< std::endl;
    }

    if (!attackTexture.loadFromFile(attackTextureFile)) {
        std::cerr << "Ошибка загрузки текстуры атаки из " << attackTextureFile << std::endl;
    }

    if (!deathTexture.loadFromFile(deathTextureFile)) {
        std::cerr << "Ошибка загрузки текстуры атаки из " << attackTextureFile << std::endl;
    }

    sprite.setTexture(texture); 

    position = sf::Vector2f(posX, posY); // Инициализируем позицию врага
    sprite.setPosition(position); 

    sprite.setTextureRect(sf::IntRect(50, 60, 35, 70)); 
}

void Enemy::animate(float deltaTime) {
    elapsedTime += deltaTime;

    if (elapsedTime >= animationSpeed) {
        currentFrame = (currentFrame) % 5; 
        int frameWidth = 95 + 35; 
        int frameHeight = 70; 
        
        sprite.setTextureRect(sf::IntRect(30 + currentFrame * frameWidth, 60, 50, frameHeight));
        currentFrame++;
        
        elapsedTime = 0.f; 
    }
}

void Enemy::attackAnimate(float deltaTime) {
    attackElapsedTime += deltaTime;

    if (attackFrame == 0) {
        sprite.setTexture(attackTexture); 
        sprite.setTextureRect(sf::IntRect(45, 64, 52, 66)); // Устанавливаем начальный кадр
    }

    if (attackElapsedTime >= attackAnimationSpeed) {
        attackFrame = (attackFrame + 1) % 4; 
            
        int frameWidth = 65 + 63; 
        int frameHeight = 66; 
            
        sprite.setTexture(attackTexture);
        sprite.setTextureRect(sf::IntRect(45 + attackFrame * frameWidth, 64, 70, frameHeight)); 
            
        attackElapsedTime = 0.f; 
    }

    sprite.setPosition(position.x, position.y + 4.f); 

}

void Enemy::deathAnimation(float deltaTime){
    deathElapsedTime += deltaTime;

    if (deathFrame == 4){
        sprite.setPosition(position.x, position.y + 9.f); 
        return;
    }

    if (deathElapsedTime >= deathAnimationSpeed) {
        deathFrame = (deathFrame) % 4; 

        int frameWidth = 71 + 40; 
        int frameHeight = 61; 

        sprite.setTexture(deathTexture);
        sprite.setTextureRect(sf::IntRect(41 + deathFrame * frameWidth, 68, frameWidth, frameHeight));
        sprite.setPosition(position.x, position.y + 9.f); 
        
        deathFrame += 1;
        deathElapsedTime = 0.f; 
    }
}

void Enemy::move(float deltaX, float deltaY, const Map& map) {
    size_t newX;
    if (movingRight) {
        newX = static_cast<size_t>(((position.x + deltaX + 40.f) / tileSize));
    } else {
        newX = static_cast<size_t>(((position.x - deltaX - 40.f) / tileSize));
    }

    size_t newY1 = static_cast<size_t>((position.y + deltaY + 40.f) / tileSize);
    size_t newY2 = static_cast<size_t>((position.y + deltaY + 10.f) / tileSize);

    size_t underY = static_cast<size_t>((position.y + 80.f) / tileSize);

    int tileType1 = map.getTileType(newX, newY1);
    int tileType2 = map.getTileType(newX, underY);
    int tileType3 = map.getTileType(newX, newY2);
    
    if ((tileType1 == -1 || tileType1 >= 40) && (tileType2 != -1 && tileType2 < 40) && 
    (tileType3 == -1 || tileType3 >= 40)) {  
        position.x += deltaX;
        position.y += deltaY;
        sprite.setPosition(position); 
    } else {
        // Если столкнулись со стеной, меняем направление движения
        movingRight = !movingRight; 
    }
}

void Enemy::update(float deltaTime, const Map& map, Entity &player, const std::vector<Explosion>& explosions) {

    // Проверка на столкновение с взрывами
    for (const auto& explosion : explosions) {
        if (getBounds().intersects(explosion.getBounds())) {
            isAllive = false;
            std::cout << "enemy died" << std::endl;
            //return; // Выходим из метода после смерти
        }
    }

    if (!flag) {
        attackAnimate(deltaTime);
        flag = true;
    }
    
    if (isAllive) {
        if (canSeePlayer(player, map)) {
            if (true){
            std::cout<<"противник видит игрока, останавливаемся и начинаем стрелять"<<std::endl;
            flag = false;
            }
            lastShotTime += deltaTime;
            if (lastShotTime >= shootCooldown) {
                shoot(player.getPosition());
                lastShotTime = 0.f; 
            }

            attackAnimate(deltaTime);
            attackFlag = true;
            sprite.setScale(movingRight ? 1.f : -1.f, 1.f);
        } else if (attackFlag){
            sprite.setTexture(texture);
            sprite.setTextureRect(sf::IntRect(50, 60, 35, 70)); 
            attackFlag = false;
        } else {
            sf::Vector2f enemyPosition = sprite.getPosition();
            sf::Vector2f playerPosition = player.getPosition();
            float distanceToPlayer = std::sqrt(std::pow(playerPosition.x - enemyPosition.x, 2) + 
                                                    std::pow(playerPosition.y - enemyPosition.y, 2));
            if (distanceToPlayer < 64.f) { 
                    // Поворачиваем врага в сторону игрока
                if (playerPosition.x < enemyPosition.x) {
                    movingRight = false; 
                } else {
                    movingRight = true;
                }
                sprite.setScale(movingRight ? 1.f : -1.f, 1.f); 
            }
            animate(deltaTime);
            // Если не видит игрока, продолжаем движение
            float direction = movingRight ? speed * deltaTime : -speed * deltaTime;
            move(direction, 0.f, map); 

            sprite.setScale(movingRight ? 1.f : -1.f, 1.f); 
        } 
    } else {
        deathAnimation(deltaTime);
    }
        for (size_t i = 0; i < bullets.size(); ) {
        bullets[i].update(deltaTime); 

        size_t bulletX = static_cast<size_t>(bullets[i].getPosition().x / tileSize);
        size_t bulletY = static_cast<size_t>(bullets[i].getPosition().y / tileSize);
        
        int tileType = map.getTileType(bulletX, bulletY);
        
        if (tileType != -1 && tileType < 40 ) { // Если тайл не проходимый
            bullets.erase(bullets.begin() + i); // Удаляем пулю из вектора
        } else {
           if (checkCollisionWithPlayer(bullets[i], player)) {
                player.die(); 
                bullets.erase(bullets.begin() + i); 
            } else {
                ++i; 
            }
        }
    } 
}

bool Enemy::checkCollisionWithPlayer(const Bullet& bullet, const Entity& player) const {
    return bullet.getShape().getGlobalBounds().intersects(player.getBounds());
}

void Enemy::draw(sf::RenderWindow& window) {
   window.draw(sprite);
    
   for (auto& bullet : bullets) {
       bullet.draw(window);
   }
}

void Enemy::shoot(const sf::Vector2f& playerPosition) {
    float bulletStartX = movingRight ? position.x + sprite.getGlobalBounds().width 
    : position.x - sprite.getGlobalBounds().width;
    bullets.emplace_back(bulletStartX, position.y + yShoot, playerPosition);
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
        if (tileType != -1 && tileType < 40)  { // Если не проходимый тайл
            return false; // Есть стена между противником и игроком
        }
    }

    return true; // Противник видит игрока
}