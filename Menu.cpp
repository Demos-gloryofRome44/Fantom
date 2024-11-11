#include "Menu.hpp"

void Menu::show(sf::RenderWindow& window) {
    // Создаем текст для меню
    sf::Font font;
    if (!font.loadFromFile("assets/DsStamper.ttf")) { // Замените на путь к вашему шрифту
        std::cerr << "Ошибка загрузки шрифта" << std::endl;
        return;
    }

    sf::Text title("Fantom \n Dark Entity", font, 50);
    title.setPosition(400, 100);

    sf::Text startButton("Start Game", font, 30);
    startButton.setPosition(450, 250);

    sf::Text settingsButton("Settings", font, 30);
    settingsButton.setPosition(450, 300);

    while (true) {
        window.clear();
        window.draw(title);
        window.draw(startButton);
        window.draw(settingsButton);
        window.display();

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close(); // Закрытие окна при нажатии на крестик
                return; // Выход из меню
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    // Проверка нажатия кнопки "Start Game"
                    if (startButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        std::cout << "Начало игры..." << std::endl;
                        window.close(); // Закрытие окна при нажатии на "Start Game"
                        return; // Выход из меню
                    }
                    else if (settingsButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                        // Логика для открытия настроек
                        std::cout << "Настройки не реализованы." << std::endl;
                    }
                }
            }
        }
    }
}