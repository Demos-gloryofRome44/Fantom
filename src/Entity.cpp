#include "include/Entity.hpp"
#include "include/Map.hpp"

Entity::Entity(const std::string& texturePlayer, const std::string& turnTexturePlayer,
const std::vector<std::string>& dieTexturesFile, float posX, float posY, float width, float height)
    : currentFrame(0), animationSpeed(0.1f), elapsedTime(0.f), deathAnimationSpeed(0.3f), 
    currentDeathFrame(0), deathElapsedTime(0.f){
    
    
        if (!texture.loadFromFile(texturePlayer)) {
            std::cerr << "Ошибка загрузки текстуры из " << texturePlayer << std::endl;
        } 

        if (!turnTexture.loadFromFile(turnTexturePlayer)) {
            std::cerr << "Ошибка загрузки текстуры из " << turnTexturePlayer << std::endl;
        } 

    for (const auto& file : dieTexturesFile) {
        sf::Texture dieTexture;
        if (!dieTexture.loadFromFile(file)) {
            std::cerr << "Ошибка загрузки текстуры из " << file << std::endl;
        } else {
            dieTextures.push_back(dieTexture); 
        }
    }


    sprite.setTexture(texture); 

    sprite.setPosition(posX, posY); 

    sprite.setTextureRect(sf::IntRect(143, 30, 220, 290));

    scaleX = width / (sprite.getLocalBounds().width * 21); 
    scaleY = height / (sprite.getLocalBounds().height * 11);

    sprite.setScale(scaleX, scaleY);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    std::cout << "New Bounds: " << bounds.left << ", " << bounds.top 
              << ", " << bounds.width << ", " << bounds.height << std::endl;
}

void Entity::move(float x, float y, Map &map) {
    sf::Vector2f currentPosition = sprite.getPosition();

    sprite.move(x, y);

    // Проверка на столкновение
    if (checkCollision(map)) {
        // Если произошло столкновение, возвращаемся к старому положению
        sprite.setPosition(currentPosition);
    } 
}

void Entity::updateSprite(bool turn) {
    if (turn) {
        sprite.setTexture(turnTexture); // Устанавливаем текстуру для поворота
    } else {
        sprite.setTexture(texture); // Устанавливаем обычную текстуру
    }
}

/* текстуры весом < 40 это стены
*  текстуры >40 это фоновые обьекты 
*  -1 - фон
*  11 и 29 - двери
*  50 - терминал открытия
*  100 - кристал
*/
bool Entity::checkCollision(Map& map) {
    // Получаем границы игрока
    sf::FloatRect playerBounds = getBounds();

    // Проходим по всем тайлам карты
    for (size_t y = 0; y < map.getHeight(); ++y) {
        for (size_t x = 0; x < map.getWidth(); ++x) {
            sf::FloatRect tileBounds = map.getTileBounds(x, y); 

            int tileType = map.getTileType(x, y); 

            if (tileType == 100) {
                sf::Vector2f crystalPosition(x * map.getTileSize(), y * map.getTileSize());
                if (playerBounds.intersects(tileBounds)) {
                    if (std::find(map.visitedCrystals.begin(), map.visitedCrystals.end(), crystalPosition) == map.visitedCrystals.end()) {
                        map.visitedCrystals.emplace_back(crystalPosition); // Добавляем позицию кристалла
                        std::cout << "Кристалл собран!" << std::endl; 
                        maxEnergy += 50.f;
                        showEnergyIncreaseMessage();
                    }
                }
            }

            if (tileType == 50) {                
                if (playerBounds.intersects(tileBounds)) {
                    doorActivation = true;
                    map.setDoorActivation(doorActivation);
                }
            }

            if ((tileType == 11 || tileType == 29) && doorActivation) {
                sf::FloatRect back = map.getTileBounds(x, y - 1);
                if (playerBounds.intersects(tileBounds)) {
                    return false; 
                }
                if (playerBounds.intersects(back)) {
                    return false; 
                }
            }
            
            if (tileType != -1 && tileType < 40) {              
                if (playerBounds.intersects(tileBounds)) {
                    return true; 
                }
            }
        }
    }
    
    return false; // Столкновение не обнаружено
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void Entity::update(float deltaTime) {
    if (!isAlive) {
        deathElapsedTime += deltaTime;

        if (currentDeathFrame == dieTextures.size() - 11) {
            std::cout << "Анимация смерти завершена." << std::endl;
            end = true;
            return;
        }

        if (deathElapsedTime >= deathAnimationSpeed) {
            currentDeathFrame = (currentDeathFrame); 
            
            sprite.setTexture(dieTextures[currentDeathFrame]); 
            sprite.setTextureRect(sf::IntRect(50, 20, 305, 350));
             
            flyingDeath = true;
            deathElapsedTime = 0.f; 
            currentDeathFrame += 1;    
        }
    }
}

sf::Vector2f Entity::getPosition() const {
    return sprite.getPosition(); 
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y); 
}

void Entity::die() {
    if (!isAlive) return; 

    isAlive = false; 

    std::cout << "Игрок умер!" << std::endl;
}

bool Entity::isOnGround(Map &map) {
   return checkCollision(map); 
}

void Entity::showEnergyIncreaseMessage() {
    if (!font.loadFromFile("assets/DsStamper.ttf")) { 
        std::cerr << "Ошибка загрузки шрифта!" << std::endl;
    }
    std::cout << "Максимальная энергия увеличена: " << maxEnergy;
    
    messageText.setFont(font); 
    messageText.setString("death is comming"); 
    messageText.setCharacterSize(30); 
    messageText.setFillColor(sf::Color::Red); 

    messageText.setPosition(130.f, 100.f);
    showMessage = true;
}