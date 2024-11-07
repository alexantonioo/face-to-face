#pragma once
#include <SFML/Graphics.hpp>


class Collision
{
    public:

    
    Collision(const sf::Vector2f& position, const sf::Vector2f& size);
    
    void draw(sf::RenderWindow& window);

    const sf::RectangleShape& getShape() const;
    
    bool intersects(const sf::RectangleShape& OpponetRectangle) const;
    
    void move(sf::Vector2f direction);
    
    sf::RectangleShape rectangle;

};