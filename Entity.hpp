#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"

class Entity {
public:
    sf::CircleShape circle;
    sf::Texture texture;
    sf::Sprite sprite;

    // Конструктор
    Entity(const std::string& textureFile, float posX, float posY, float width, float height);

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    bool checkCollision(const Map& map);
    
    void move(float x, float y, const Map& map);
    void draw(sf::RenderWindow& window);
};

#endif // ENTITY_H