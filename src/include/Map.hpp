#ifndef MAP_HPP
#define MAP_HPP

#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "Enemy.hpp"
#include "Entity.hpp"

class Entity;
class Enemy;
class Explosion;
class Map {
public:
    // Конструктор, который загружает текстуры и устанавливает соответствующую карту
    Map(const std::unordered_map<int, std::string>& textureFiles, const std::vector<std::vector<int>>& mapData, 
    int currentMap);

    // Метод для отрисовки карты
    void draw(sf::RenderWindow& window);

    int getWidth() const { return map.empty() ? 0 : map[0].size(); } // Возвращает ширину карты
    int getHeight() const { return map.size(); } // высота
    
    int getTileType(size_t x, size_t y) const { return map[y][x]; } // Получение типа тайла
    float getTileSize() const {return tileSize; }
    sf::FloatRect getTileBounds(size_t x, size_t y) const; // Получение границ тайла

    void updateEnemies(float deltaTime, Entity &player, const std::vector<Explosion>& explosions); // Новый метод для обновления противников

    bool isExitTile(const sf::Vector2f& position) const;
    bool isExitTileEnd(const sf::Vector2f& position) const;

    void update(float deltaTime);
    bool doorActivation = false;
    void setDoorActivation(bool activation) {doorActivation = activation; }

    std::vector<sf::Vector2f> visitedCrystals; // Вектор для хранения позиций кристаллов
private:
    sf::Texture backgroundTexture; // Текстура для фона
     sf::Sprite backgroundSprite;   // Спрайт для фона
    std::unordered_map<int, sf::Texture> textures; // Вектор текстур
    std::vector<std::vector<int>> map;  // Двумерный массив для карты
    const float tileSize = 32.f;        // Размер тайла (можно изменить)

    std::vector<Enemy> enemies;

    int currentDoorFrame = 0; 
    float doorAnimationTime = 0.f; // Время анимации
    const float doorFrameDuration = 0.1f; // Длительность одного


};

#endif // MAP_HPP