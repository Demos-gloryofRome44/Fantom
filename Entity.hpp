#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"

class Map;
class Entity {
public:
    sf::Texture texture;
    sf::Texture dieTexture;
    sf::Sprite sprite;
    sf::CircleShape circle;
    std::vector<sf::Texture> textures; // Вектор для хранения 
    std::vector<sf::Texture> dieTextures;
    int currentFrame; // Текущий кадр анимации
    int currentDeathFrame; // Текущий кадр анимации смерти
    float animationSpeed; // Скорость анимации
    float deathAnimationSpeed; // Скорость анимации смерти
    float elapsedTime;
    float deathElapsedTime; // Время для анимации смерти

    // Конструктор
    Entity(const std::vector<std::string>& textureFiles, const std::vector<std::string>& dieTextures,
     float posX, float posY, float width, float height);

    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }

    bool checkCollision(Map& map);
    bool right = true;
    bool left = false;
    
    void move(float x, float y, Map& map);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime); // Метод обновления анимации

    void updateSprite(bool turn);

    sf::Vector2f getPosition() const;
    void setPosition(float x, float y); 

    void resetState();

    void die();
    bool isAlive = true;
    bool end = false;

    bool doorActivation = false;
};

#endif // ENTITY_H