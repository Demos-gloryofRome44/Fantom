#include "Bullet.hpp"

Bullet::Bullet(float x, float y, const sf::Vector2f& playerPosition)
    : speed(200.f) { // Установите скорость по вашему усмотрению
    shape.setRadius(3.f);
    shape.setPosition(x, y);
    shape.setFillColor(sf::Color::Red);

    // Вычисляем направление к игроку
    sf::Vector2f direction = playerPosition - sf::Vector2f(x, y); // Вектор от пули к игроку

    // Нормализуем направление
    float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (distance != 0) {
        direction /= distance; // Нормализация
    }

    // Устанавливаем скорость по направлению к игроку
    velocity = direction * speed; // Устанавливаем скорость как нормализованный вектор, умноженный на скорость
}

void Bullet::update(float deltaTime) {
    shape.move(velocity * deltaTime); // Движение по направлению к игроку
}

void Bullet::draw(sf::RenderWindow& window) {
    window.draw(shape); // Отрисовка пули
}

sf::Vector2f Bullet::getPosition() const {
    return shape.getPosition(); // Возвращаем позицию формы пули
}