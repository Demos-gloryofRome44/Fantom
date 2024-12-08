#ifndef RESOURCE_LOADER_H
#define RESOURCE_LOADER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

class ResourceLoader {
public:
    // Загружает текстуры из указанной директории
    std::vector<std::string> loadTexturesFromDirectory(const std::string& directory) {
        std::vector<std::string> textureFiles;

        // Проверка существования директории
        if (!std::filesystem::exists(directory)) {
            std::cerr << "Директория не найдена: " << directory << std::endl;
            return textureFiles; // Возвращаем пустой вектор
        }

        // Проходим по всем файлам в директории
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.is_regular_file()) { // Проверяем, что это файл
                const std::string& path = entry.path().string();
                if (path.ends_with(".png") || path.ends_with(".jpg") || path.ends_with(".jpeg")) {
                    textureFiles.push_back(path); // Добавляем путь к файлу в вектор
                }
            }
        }

        return textureFiles; // Возвращаем список загруженных текстур
    }

    // Загружает текстуры из файла, где каждая строка имеет формат: id путь_к_текстуре
    std::unordered_map<int, std::string> loadTextures(const std::string& filename) {
        std::unordered_map<int, std::string> textureFiles;
        std::ifstream file(filename);
        std::string line;

        while (std::getline(file, line)) {
            std::istringstream iss(line);
            int id;
            std::string path;
            char delimiter;

            if (iss >> id >> delimiter >> path) {
                textureFiles[id] = path; // Добавляем путь к текстуре с соответствующим ID
            }
        }
        return textureFiles; 
    }

    // Загружает карты из файла
    std::vector<std::vector<std::vector<int>>> loadMapsFromFile(const std::string& filename) {
        std::ifstream file(filename);
        std::vector<std::vector<std::vector<int>>> allMaps;
        std::vector<std::vector<int>> currentMap;

        if (!file.is_open()) {
            std::cerr << "Не удалось открыть файл: " << filename << std::endl;
            return allMaps; 
        }

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) {
                if (!currentMap.empty()) {
                    allMaps.push_back(currentMap);
                    currentMap.clear(); 
                }
                continue; 
            }

            if (line[0] == '#') { 
                continue; 
            }

            std::istringstream iss(line);
            std::vector<int> row;
            int value;

            while (iss >> value) { // Читаем значения карты
                row.push_back(value);
            }

            currentMap.push_back(row); // Добавляем строку в текущую карту
        }

        if (!currentMap.empty()) { 
            allMaps.push_back(currentMap);
        }

        return allMaps; // Возвращаем все загруженные карты
    }
};

#endif // RESOURCE_LOADER_H