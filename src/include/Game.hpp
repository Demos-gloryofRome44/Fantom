#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "Map.hpp"
#include "Explosion.hpp"
#include "ResourceLoader.hpp"
#include <memory>
#include <thread>
#include <mutex>


class Game {
public:
    Game();
    void run();

    void draw();
    void processEvents();
    void update();

    void triggerExplosion(sf::Vector2f position);

    bool isGameOver = false;


private:
    sf::RenderWindow window;

    ResourceLoader loader;

    Entity player;

    // флаги для движения игрока в зависимости прожатой кнопки
    bool movingUp;
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    bool right = false;
    bool left = false;
    bool turn = true;

    sf::Clock gameClock; 

    const float speed = 0.08f; // Увеличиваем скорость

    std::vector<Map> maps; // Вектор для хранения разных карт игры
    int currentMapIndex = 0; 

    std::vector<Explosion> explosions;
    float explosionCooldown = 1.0f; // Время между взрывами 
    float lastExplosionTime = 0.0f; // Время последнего взрыва
    float totalTime = 0.0f;
    int totalCrystel = 0;

    // Полоска энергии
    sf::RectangleShape energyBarBackground; 
    sf::RectangleShape energyBar; 

    sf::Font font;
    sf::Text timeText; // Кнопка "Новая игра"

    int previousMapIndex;
};
#endif // GAME_H