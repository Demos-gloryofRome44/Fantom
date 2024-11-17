#include "Bullet.hpp"

Bullet::Bullet(float x, float y, float speed)
    : speed(speed) {
    shape.setRadius(5.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);
}

void Bullet::update(float deltaTime) {
    shape.move(speed * deltaTime, 0); // Движение вправо
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape); // Отрисовка пули
}