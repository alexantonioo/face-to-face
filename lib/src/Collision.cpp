#include "Collision.hpp"


Collision::Collision(const sf::Vector2f& position, const sf::Vector2f& size)
    :rectangle(size), originalSize(size)
{
    rectangle.setOrigin(size / 2.f);  
    rectangle.setPosition(position);
    rectangle.setPosition(position);
    rectangle.setFillColor(sf::Color::Transparent);
    rectangle.setOutlineColor(sf::Color::Transparent);
    rectangle.setOutlineThickness(4);
    rectangle.setOrigin(sf::Vector2f(size.x/2, size.y/2));
     
}

const sf::RectangleShape& Collision::getShape() const {
    return rectangle;
}

bool Collision::intersects(const sf::RectangleShape& OpponetRectangle) const {
    return rectangle.getGlobalBounds().intersects(OpponetRectangle.getGlobalBounds());
}

void Collision::draw(sf::RenderWindow& window) {
    window.draw(rectangle);
} 

void Collision::move(sf::Vector2f direction)
{
    rectangle.move(direction);
}

sf::Vector2f Collision::getPosition()
{
    return rectangle.getPosition();
}

sf::Vector2f Collision::getSize()
{
    return rectangle.getSize();
}

void Collision::setPosition(sf::Vector2f position)
{
    rectangle.setPosition(position);
}
