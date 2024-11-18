#ifndef MAP_HPP
#define MAP_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Entity.hpp"

class Entity;
class Enemy;
class Map {
public:
    // Конструктор, который загружает текстуры и устанавливает карту
    Map(const std::vector<std::string>& textureFiles, const std::vector<std::vector<int>>& mapData);

    // Метод для отрисовки карты
    void draw(sf::RenderWindow& window);

    int getWidth() const { return map.empty() ? 0 : map[0].size(); } // Возвращает ширину карты
    int getHeight() const { return map.size(); } // высота
    
    int getTileType(size_t x, size_t y) const { return map[y][x]; } // Получение типа тайла
    float getTileSize() const {return tileSize; }
    sf::FloatRect getTileBounds(size_t x, size_t y) const; // Получение границ тайла

    void updateEnemies(float deltaTime, Entity &player); // Новый метод для обновления противников

private:
    sf::Texture backgroundTexture; // Текстура для фона
    sf::Sprite backgroundSprite;    // Спрайт для фона
    std::vector<sf::Texture> textures; // Вектор текстур
    std::vector<std::vector<int>> map;  // Двумерный массив для карты
    const float tileSize = 32.f;        // Размер тайла (можно изменить)

    std::vector<Enemy> enemies;
};

#endif // MAP_HPP