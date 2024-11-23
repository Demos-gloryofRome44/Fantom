#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Entity.hpp"
#include "Map.hpp"
#include "Game.hpp"
#include "Menu.hpp"

int main() {
    std::cout<<"New Game start123"<< std::endl;

    sf::RenderWindow window(sf::VideoMode(1200, 700), "Main Menu");
    sf::Music backgroundMusic; 

    if (!backgroundMusic.openFromFile("assets/song18.mp3")) { 
        std::cerr << "Ошибка загрузки музыки!" << std::endl;
    }
    backgroundMusic.setLoop(true); 
    backgroundMusic.play();

    Menu menu; 
    menu.show(window);
    Game game;
    game.run();

    return 0;
}