#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>
#include "Map.hpp"

class Map;
class Bullet {
public:
    Bullet(float x, float y, const sf::Vector2f& playerPosition);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::CircleShape getShape() const;
    sf::Vector2f getPosition() const;

private:
    sf::CircleShape shape;
    float speed;
    sf::Vector2f velocity; // Направление и скорость пули
};

#endif // BULLET_HPP