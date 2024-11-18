#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"
#include "Entity.hpp"
#include "Map.hpp"

class Map;
class Entity;
class Bullet;
class Enemy {
public:
    Enemy(const std::string& textureFile, const std::string& AttackTextureFile, float posX, float posY, float width, float height);
    
    void update(float deltaTime, const Map& map, const Entity &player);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite; // Спрайт для отображения противника
    sf::Texture texture; // Текстура для движения
    sf::Texture attackTexture; // Текстура для атаки
    std::vector<Bullet> bullets; // Вектор для хранения пуль
    float speed; // Скорость движения противника
    float shootCooldown; // Время между выстрелами
    float lastShotTime; // Время с последнего выстрела
    int currentFrame; // Индекс текущего кадра анимации движения
    int attackFrame; // Индекс текущего кадра анимации атаки
    float animationSpeed; // Скорость анимации движения
    float attackAnimationSpeed; // Скорость анимации атаки
    float elapsedTime; // Время с последнего обновления кадра
    float attackElapsedTime; // Время с последнего обновления кадра атаки
    bool attackFlag = false;

    sf::Vector2f position; // Позиция врага
    const float tileSize = 32.f; // Размер тайла для проверки коллизий

    void animate(float deltaTime); // Метод для анимации движения
    void attackAnimate(float deltaTime); // Метод для анимации атаки
    void move(float deltaX, float deltaY, const Map& map); // Метод для движения с проверкой тайлов
    void shoot(const Entity& player); // Метод для стрельбы

    bool movingRight;

    bool canSeePlayer(const Entity& player, const Map& map);
    bool flag = true;
};

#endif // ENEMY_HPP

