#ifndef BULLET_HPP
#define BULLET_HPP

#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y, float speed);
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    sf::CircleShape getShape() const;

private:
    sf::CircleShape shape;
    float speed;
};

#endif // BULLET_HPP