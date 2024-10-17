#include "Ring.hpp"
#include "iostream"

Ring::Ring(float width, float height, const std::string& texturePath) 
{
    // Cargar la textura del ring
    if (!ringTexture_.loadFromFile(texturePath)) {
        std::cerr << "!!Error loading ring texture: " << texturePath << std::endl;
    } else {
        ringSprite_.setTexture(ringTexture_);
        ringSprite_.setScale(width / ringTexture_.getSize().x, height / ringTexture_.getSize().y);
        ringSprite_.setPosition(100, 100);  
    }
}

void Ring::draw(sf::RenderWindow& window) {
    window.draw(ringSprite_);
}

sf::FloatRect Ring::getBounds() const {
    return ringSprite_.getGlobalBounds();
}