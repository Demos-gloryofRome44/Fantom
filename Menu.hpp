#ifndef MENU_HPP
#define MENU_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.hpp"

class Menu {
public:
    void show(sf::RenderWindow& window);
    int restartMenu(sf::RenderWindow& window ); // Метод для перезапуска игры

    void displayResults(sf::RenderWindow& window, float time, int crystals);

private:
    sf::Text title;
    sf::Text startButton;
    sf::Text settingsButton;

    sf::Font font; // Шрифт для кнопок
    sf::Text newGameButton; // Кнопка "Новая игра"
    sf::Text exitButton; // Кнопка "Выход"
};
#endif // MENU_HPP