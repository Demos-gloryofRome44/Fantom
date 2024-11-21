#include "Menu.hpp"

void Menu::show(sf::RenderWindow& window) {
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 

    window.clear();

    if (!font.loadFromFile("assets/DsStamper.ttf")) { 
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return;
    } 

     if (!backgroundTexture.loadFromFile("assets/back.png")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture); 

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
    

    sf::Text title("Fantom \n Dark Entity", font, 50);
    title.setPosition(470, 140);

    sf::Text startButton("Start Game", font, 30);
    startButton.setPosition(520, 310);
    startButton.setFillColor(sf::Color::Black);

    sf::Text settingsButton("Settings", font, 30);
    settingsButton.setPosition(520, 350);
    settingsButton.setFillColor(sf::Color::Black);

    while (true) {
        window.clear();

        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(startButton);
        window.draw(settingsButton);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрытие окна при нажатии на крестик
                return; 
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Проверка нажатия кнопки "Start Game"
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Начало игры..." << std::endl;
                        window.close(); // Закрытие окна при нажатии на "Start Game"
                        return; 
                    }
                    else if (settingsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Настройки не реализованы." << std::endl;
                    }
                }
            }
        }
    }
}

int Menu::restartMenu(sf::RenderWindow& window) {
    // Загрузка шрифта
    if (!font.loadFromFile("assets/DsStamper.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return -1;
    }

    // Настройка кнопок
    newGameButton.setFont(font);
    newGameButton.setString("New Game");
    newGameButton.setCharacterSize(30);
    newGameButton.setPosition(200, 200); 

    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(30);
    exitButton.setPosition(200, 150); 

    while (true) {
        
        window.draw(newGameButton);
        window.draw(exitButton);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return -1;
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newGameButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        return 1; 
                    } else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close(); 
                        return 2; 
                    }
                }
            }
        }
    }
}