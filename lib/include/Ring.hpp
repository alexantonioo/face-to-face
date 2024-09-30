#pragma once
#include <SFML/Graphics.hpp>

class Ring 
{
    public:
        Ring(float width, float height);

        void draw(sf::RenderWindow& window);

        sf::FloatRect getBounds() const;

    private:
        sf::RectangleShape ringShape;
        sf::RectangleShape topBorder, bottomBorder, leftBorder, rightBorder;
};

