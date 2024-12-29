#include <SFML/Graphics.hpp>
#include <iostream>

#pragma once
class Explosion {
public:
    Explosion(float x, float y) : scale(0.0f), growing(true), elapsedTime(0.f), animationSpeed(0.1f) {
        if (!texture.loadFromFile("assets/boom.png")) { 
            std::cerr << "Ошибка загрузки текстуры взрыва." << std::endl;
        }
        sprite.setTexture(texture);
        sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f); // Устанавливаем центр для поворота
        sprite.setPosition(x, y);
    }

    void update(float deltaTime) {
        elapsedTime += deltaTime;

        // Увеличиваем или уменьшаем масштаб
        if (growing) {
            scale += deltaTime; 
            if (scale >= 0.3f) { 
                growing = false; 
            }
        } else {
            scale -= deltaTime; 
            if (scale <= 0.0f) {
                scale = 0.0f; // Завершение анимации
            }
        }

        sprite.setScale(scale, scale); 
    }

    void draw(sf::RenderWindow& window) {
        if (scale > 0.0f) { // Рисуем только если масштаб больше 0
            window.draw(sprite);
        }
    }

    bool isFinished() const {
        return scale <= 0.0f;
    }

    sf::FloatRect getBounds() const {
        return sprite.getGlobalBounds(); 
    }

private:
    sf::Texture texture;
    sf::Sprite sprite;
    float scale;
    bool growing;
    float elapsedTime;
    float animationSpeed;
};