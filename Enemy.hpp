#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"
#include "Entity.hpp"

class Map;
class Enemy {
public:
    Enemy(const std::string& textureFile, float posX, float posY, float width, float height);
    
    void update(float deltaTime, const Map& map);
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite; // Спрайт для отображения противника
    sf::Texture texture; // Текстура противника
    std::vector<Bullet> bullets; // Вектор для хранения пуль
    float speed; // Скорость движения противника
    float shootCooldown; // Время между выстрелами
    float lastShotTime; // Время с последнего выстрела
    int currentFrame; // Индекс текущего кадра анимации
    float animationSpeed; // Скорость анимации
    float elapsedTime; // Время с последнего обновления кадра

    sf::Vector2f position; // Позиция врага
    const float tileSize = 32.f; // Размер тайла для проверки коллизий

    void animate(float deltaTime); // Метод для анимации
    void move(float deltaX, float deltaY, const Map& map); // Метод для движения с проверкой тайлов
    void shoot(); // Метод для стрельбы

    bool movingRight;

    bool canSeePlayer(const Entity& player, const Map& map)
};

#endif // ENEMY_HPP

