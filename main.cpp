#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "include/Entity.hpp"
#include "include/Map.hpp"
#include "include/Game.hpp"
#include "include/Menu.hpp"

int main() {
    std::cout<<"New Game start123"<< std::endl;

    sf::RenderWindow window(sf::VideoMode(512, 320), "Main Menu");
    sf::Music backgroundMusic; 

    if (!backgroundMusic.openFromFile("assets/song18.mp3")) { 
        std::cerr << "Ошибка загрузки музыки!" << std::endl;
    }
    backgroundMusic.setLoop(true); 
    backgroundMusic.play();

    Menu menu; 
    menu.show(window);

    std::unique_ptr<Game> game = std::make_unique<Game>(); // Используем уникальный указатель

    while (true) {
        game->run();

        if (!game->isGameOver) {
            game = std::make_unique<Game>(); // Создаем новый экземпляр Game
        } else {
            break;
        }

        window.clear();
        // Отрисовка элементов здесь
        window.display();
    }

    return 0;
}