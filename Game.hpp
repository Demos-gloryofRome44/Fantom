#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "Map.hpp"
#include "Explosion.hpp"


class Game {
public:
    Game();
    bool run();
    void processEvents();
    void update();
    void restart();

    void triggerExplosion(sf::Vector2f position);

private:
    sf::RenderWindow window;
    
    Entity player;

    bool movingUp;// движение игрока в зависимости прожатой кнопки
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    bool right = false;
    bool left = false;
    bool turn = true;

    sf::Clock gameClock; 

    const float speed = 0.05f; // Увеличиваем скорость

    bool isGameOver = false;

    std::vector<Map> maps; // Вектор для хранения разных карт
    int currentMapIndex = 0; // Индекс текущей карты

    std::vector<Explosion> explosions;
    float explosionCooldown = 1.0f; // Время между взрывами (в секундах)
    float lastExplosionTime = 0.0f; // Время последнего взрыва

    // Полоска энергии
    sf::RectangleShape energyBarBackground; 
    sf::RectangleShape energyBar; 

};
#endif // GAME_H