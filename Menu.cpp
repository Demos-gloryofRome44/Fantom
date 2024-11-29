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

     if (!backgroundTexture.loadFromFile("assets/image.jpg")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture); 

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );
    

    sf::Text title("Fantom\n             Dark Entity", font, 30);
    title.setPosition(80, 30);

    sf::Text startButton("Start Game", font, 20);
    startButton.setPosition(210, 160);

    sf::Text settingsButton("Settings", font, 20);
    settingsButton.setPosition(210, 190);

    while (true) {
        window.clear();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); 
                return; 
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Начало игры..." << std::endl;
                        window.close(); 
                        return; 
                    }
                    else if (settingsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Настройки не реализованы." << std::endl;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (startButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    startButton.setFillColor(sf::Color(255, 0, 0)); 
                } else {
                    startButton.setFillColor(sf::Color::White); 
                }

                if (settingsButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    settingsButton.setFillColor(sf::Color(255, 0, 0)); 
                } else {
                    settingsButton.setFillColor(sf::Color::White); 
                }
            }
        }

        window.draw(backgroundSprite);
        window.draw(title);
        window.draw(startButton);
        window.draw(settingsButton);
        window.display();
    }
}

int Menu::restartMenu(sf::RenderWindow& window) {
    if (!font.loadFromFile("assets/DsStamper.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return -1;
    }

    newGameButton.setFont(font);
    newGameButton.setString("New Game");
    newGameButton.setCharacterSize(30);
    newGameButton.setPosition(190, 100); 

    exitButton.setFont(font);
    exitButton.setString("Exit");
    exitButton.setCharacterSize(30);
    exitButton.setPosition(237, 150); 

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
                        window.clear();
                        return 1; 
                    } else if (exitButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close(); 
                        return 2; 
                    }
                }
            }

            // Подсветка кнопок при наведении курсора
            if (event.type == sf::Event::MouseMoved) {
                if (newGameButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    newGameButton.setFillColor(sf::Color(255, 0, 0));
                } else {
                    newGameButton.setFillColor(sf::Color::White); 
                }

                if (exitButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    exitButton.setFillColor(sf::Color(255, 0, 0)); 
                } else {
                    exitButton.setFillColor(sf::Color::White); 
                }
            }
        }
    }
}

void Menu::displayResults(sf::RenderWindow& window, float time, int crystals) {
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite; 

    if (!font.loadFromFile("assets/DsStamper.ttf")) {
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return;
    }

    if (!backgroundTexture.loadFromFile("assets/labs/Background/titre.jpg")) {
        std::cerr << "Ошибка загрузки текстуры фона." << std::endl;
    }

    backgroundSprite.setTexture(backgroundTexture); 

    backgroundSprite.setScale(
        static_cast<float>(window.getSize().x) / backgroundTexture.getSize().x,
        static_cast<float>(window.getSize().y) / backgroundTexture.getSize().y
    );

    std::string resultText = "Your stat: \n";
    resultText += "Total Time: " + std::to_string(time) + " seconds\n";
    resultText += "Collected Crystals: ";

    sf::Texture crystalTexture;
    if (!crystalTexture.loadFromFile("assets/labs/diamond.png")) {
        std::cerr << "Ошибка загрузки текстуры кристалла" << std::endl;
        return;
    }

    sf::Sprite crystalSprite(crystalTexture);
    crystalSprite.setScale(1.f, 1.f); 
    crystalSprite.setPosition(345, 140); 

    sf::Text text;
    text.setString(resultText + std::to_string(crystals)); 
    text.setCharacterSize(24);
    text.setFont(font); 
    text.setFillColor(sf::Color::Black);
    text.setPosition(80, 80); 

    sf::Text newGameButton;
    newGameButton.setFont(font);
    newGameButton.setString("New Game");
    newGameButton.setCharacterSize(30);
    newGameButton.setFillColor(sf::Color::Black);
    newGameButton.setPosition(170, 200); 

    while (window.isOpen()) {
        window.clear();
        window.draw(backgroundSprite);
        window.draw(text);
        window.draw(crystalSprite); 
        window.draw(newGameButton); 
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    if (newGameButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        window.close();
                        return;
                    }
                }
            }

            if (event.type == sf::Event::MouseMoved) {
                if (newGameButton.getGlobalBounds().contains(event.mouseMove.x, event.mouseMove.y)) {
                    newGameButton.setFillColor(sf::Color(255, 0, 0)); 
                } else {
                    newGameButton.setFillColor(sf::Color::Black);
                }
            }
        }
    }
}
