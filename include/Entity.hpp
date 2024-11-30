#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Map.hpp"

class Map;
class Entity {
public:
    Entity(const std::vector<std::string>& textureFiles, const std::vector<std::string>& dieTextures,
           float posX, float posY, float width, float height);

    // Методы для работы с объектом
    sf::FloatRect getBounds() const { return sprite.getGlobalBounds(); }
    bool checkCollision(Map& map);
    void move(float x, float y, Map& map);
    void draw(sf::RenderWindow& window);
    void update(float deltaTime); // Метод обновления анимации
    void updateSprite(bool turn);
    sf::Vector2f getPosition() const;
    void setPosition(float x, float y); 
    void die();
    bool isOnGround(Map &map); // Проверка на земле
    void showEnergyIncreaseMessage();

    // Параметры состояния
    bool isAlive = true;
    bool end = false;
    bool doorActivation = false;
    bool flyingDeath = false; // Флаг полета
    bool showMessage = false; 

    // Энергия
    float currentEnergy = 50.f; // Текущая энергия
    float maxEnergy = 100.f; // Максимальная энергия
    const float energyConsumptionRate = 50.f; // Расход энергии за секунду при полете
    const float energyRecoveryRate = 25.f; // Восстановление энергии в секунду

    // Сообщение о повышении энергии
    float messageDisplayTime = 0.f;
    sf::Text messageText; 

private:
    // Текстуры и спрайты
    float scaleX;
    float scaleY;
    
    sf::Texture texture;
    sf::Texture dieTexture;
    sf::Sprite sprite;
    sf::CircleShape circle;
    
    std::vector<sf::Texture> textures; // Вектор для хранения текстур
    std::vector<sf::Texture> dieTextures;

    // Анимация
    int currentFrame; 
    int currentDeathFrame; 
    float animationSpeed; 
    float deathAnimationSpeed; // Скорость анимации смерти
    float elapsedTime;
    float deathElapsedTime; // Время для анимации смерти

    bool isRight = true;

    sf::Font font; 
};

#endif // ENTITY_H