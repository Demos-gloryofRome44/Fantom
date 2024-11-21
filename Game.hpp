#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Map.hpp"


class Game {
public:
    Game();
    bool run();
    void processEvents();
    void update();
    void restart();

private:
    sf::RenderWindow window;
    //Map gameMap;
    Entity player;

        // Спрайт для фона

    bool movingUp;// движение игрока в зависимости прожатой кнопки
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    bool right = false;
    bool left = false;

    sf::Clock gameClock; 

    const float speed = 0.1f; // Увеличиваем скорость

    bool isGameOver = false;

    std::vector<Map> maps; // Вектор для хранения разных карт
    int currentMapIndex = 0; // Индекс текущей карты

};
#endif // GAME_H