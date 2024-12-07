#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "Map.hpp"
#include "Explosion.hpp"
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

    Entity player;

    bool movingUp;// движение игрока в зависимости прожатой кнопки
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    bool right = false;
    bool left = false;
    bool turn = true;

    sf::Clock gameClock; 

    const float speed = 0.08f; // Увеличиваем скорость

    std::vector<Map> maps; // Вектор для хранения разных карт
    int currentMapIndex = 0; // Индекс текущей карты

    std::vector<Explosion> explosions;
    float explosionCooldown = 1.0f; // Время между взрывами (в секундах)
    float lastExplosionTime = 0.0f; // Время последнего взрыва
    float totalTime = 0.0f;
    int totalCrystel = 0;

    // Полоска энергии
    sf::RectangleShape energyBarBackground; 
    sf::RectangleShape energyBar; 
    sf::Font font; // Шрифт для кнопок
    sf::Text timeText; // Кнопка "Новая игра"

    std::mutex mtx; // Мьютекс для синхронизации

    int previousMapIndex;


};
#endif // GAME_H