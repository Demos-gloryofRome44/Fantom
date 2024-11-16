#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Entity.hpp"
#include "Map.hpp"


class Game {
public:
    Game();
    void run();
    void processEvents();
    void update();
    
    sf::RenderWindow window;
    Map gameMap;
    Entity player;

    std::vector<std::string> frames = {"assets/entity/Walking/1.png", "assets/entity/Walking/2.png", "assets/entity/Walking/3.png", 
    "assets/entity/Walking/4.png"}; 

    sf::Texture backgroundTexture; // Текстура для фона
    sf::Sprite backgroundSprite;    // Спрайт для фона

    bool movingUp;// движение игрока в зависимости прожатой кнопки
    bool movingDown;
    bool movingLeft;
    bool movingRight;

    bool right = false;
    bool left = false;

    sf::Clock gameClock; 

    const float speed = 0.1f; // Увеличиваем скорость
};
#endif // GAME_H