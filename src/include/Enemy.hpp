#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"
#include "Entity.hpp"
#include "Map.hpp"
#include "Explosion.hpp"

class Map;
class Entity;
class Bullet;
class Enemy {
public:
    Enemy(const std::string& textureFile, const std::string& AttackTextureFile, const std::string& deathTextureFile,
    float posX, float posY, float width, float height, int yShootEnemy);
    
    void update(float deltaTime, const Map& map, Entity &player, const std::vector<Explosion>& explosions);
    void draw(sf::RenderWindow& window);

    bool checkCollisionWithPlayer(const Bullet& bullet, const Entity& player) const;

private:
    sf::Sprite sprite; // Спрайт для отображения противника

    sf::Texture texture; 
    sf::Texture attackTexture;
    sf::Texture deathTexture;

    int currentFrame; 
    int attackFrame; 
    int deathFrame;

    float animationSpeed; 
    float attackAnimationSpeed; 
    float deathAnimationSpeed;

    float elapsedTime; 
    float attackElapsedTime; 
    float deathElapsedTime;

    std::vector<Bullet> bullets; 
    float speed; 
    float shootCooldown; // Время между выстрелами
    float lastShotTime; // Время с последнего выстрела
    
    bool attackFlag = false;

    sf::Vector2f position; 
    const float tileSize = 32.f; // Размер тайла для проверки коллизий

    void animate(float deltaTime); 
    void attackAnimate(float deltaTime); 
    void deathAnimation(float deltaTime);
    bool deathFinish = false;

    void move(float deltaX, float deltaY, const Map& map); // Метод для движения с проверкой тайлов с учетом стен
    void shoot(const sf::Vector2f& playerPosition); 

    sf::FloatRect getBounds() const {
    return sprite.getGlobalBounds(); 
    }    

    bool movingRight;

    bool canSeePlayer(const Entity& player, const Map& map);
    bool flag = true;

    bool isAllive = true;

    int yShoot = 0;
};

#endif // ENEMY_HPP

