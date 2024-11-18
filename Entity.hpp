#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"

class Map;
class Entity {
public:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::CircleShape circle;
    std::vector<sf::Texture> textures; // Вектор для хранения 
    int currentFrame; // Текущий кадр анимации
    float animationSpeed; // Скорость анимации
    float elapsedTime;

    // Конструктор
    Entity(const std::vector<std::string>& textureFiles, float posX, float posY, float width, float height);

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    bool checkCollision(const Map& map);
    bool right = true;
    bool left = false;
    
    void move(float x, float y, const Map& map);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime); // Метод обновления анимации

    void updateSprite(bool turn);

    sf::Vector2f getPosition() const;
};

#endif // ENTITY_H