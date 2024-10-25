#pragma once
#include <SFML/Graphics.hpp>

class Ring 
{
    public:
        Ring(float width, float height, const std::string& texturePath);

        void draw(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;

    private:
        sf::Sprite ringSprite_;
        sf::Texture ringTexture_;
};