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
    

    void expand (const sf::Vector2f& expansionSize);
    void reset();

   
    sf::Vector2f getPosition();
    
    sf::Vector2f getSize();
    
    void setPosition(sf::Vector2f positions);

    private:

    sf::RectangleShape rectangle;
    sf::Vector2f originalSize;

    


};