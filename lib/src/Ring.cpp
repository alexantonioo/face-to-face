#include "Ring.hpp"
#include "iostream"

Ring::Ring(float width, float height, const std::string& texturePath) 
{
   // Cargar la textura del ring
    if (!ringTexture_.loadFromFile(texturePath)) {
        std::cerr << "!!Error loading ring texture: " << texturePath << std::endl;
    } else {
        ringSprite_.setTexture(ringTexture_);
        
        // Escala para ajustarse a la ventana de 800x600
        float scaleX = width / ringTexture_.getSize().x;
        float scaleY = height / ringTexture_.getSize().y;
        ringSprite_.setScale(scaleX, scaleY);
        
        // Ajustar el origen al centro de la textura
        ringSprite_.setOrigin(ringTexture_.getSize().x / 2, ringTexture_.getSize().y / 2);

        // Centrar el ring en una ventana de 800x600
        ringSprite_.setPosition(1024 / 2.0f, 768 / 2.0f);  
    }
}

void Ring::draw(sf::RenderWindow& window) {
    window.draw(ringSprite_);
}

sf::FloatRect Ring::getBounds() const {
    return ringSprite_.getGlobalBounds();
}