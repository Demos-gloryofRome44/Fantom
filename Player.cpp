Entity::Entity(std::vector<std::string>& textureFiles, float posX, float posY)
    : currentFrame(0), animationTime(0) {
    for (const auto& file : textureFiles) {
        auto texture = std::make_shared<sf::Texture>(); // Создаем shared_ptr
        if (!texture->loadFromFile(file)) {
            std::cerr << "Ошибка загрузки текстуры из " << file << std::endl;
        }
        textures.push_back(texture); // Храним указатель на текстуру
    }
    
    sprite.setTexture(*textures[currentFrame]); // Устанавливаем текстуру
    sprite.setPosition(posX, posY);
}

void Entity::update(float deltaTime) {
    animationTime += deltaTime;
    
    if (!textures.empty() && animationTime >= frameDuration) {
        currentFrame = (currentFrame + 1) % textures.size(); // Переход к следующему кадру
        sprite.setTexture(*textures[currentFrame]); // Установка нового кадра
        animationTime = 0; // Сброс времени анимации
    }
}

void Entity::move(float x, float y, const Map& map) {
    sf::Vector2f currentPosition = sprite.getPosition(); // Получаем текущее положение спрайта

    // Перемещение
    sprite.move(x, y);

    // Проверка на столкновение
    if (checkCollision(map)) {
        // Если произошло столкновение, возвращаемся к старому положению
        sprite.setPosition(currentPosition);
    }
}

bool Entity::checkCollision(const Map& map) {
    // Получаем границы игрока
    sf::FloatRect playerBounds = getBounds();

    // Проходим по всем тайлам карты
    for (size_t y = 0; y < map.getHeight(); ++y) {
        for (size_t x = 0; x < map.getWidth(); ++x) {
            int tileType = map.getTileType(x, y); // Получаем тип тайла
            
            if (tileType != -1) { // Проверяем типы блоков
                sf::FloatRect tileBounds = map.getTileBounds(x, y); // Получаем границы тайла
                
                if (playerBounds.intersects(tileBounds)) {
                    return true; // Столкновение обнаружено
                }
            }
        }
    }
    
    return false; // Столкновение не обнаружено
}

void Entity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

sf::FloatRect Entity::getBounds() const {
    return sprite.getGlobalBounds(); // Возвращаем границы спрайта
}