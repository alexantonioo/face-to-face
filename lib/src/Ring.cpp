#include "Ring.hpp"

Ring::Ring(float width, float height) 
{
    ringShape.setSize(sf::Vector2f(width, height));
    ringShape.setFillColor(sf::Color(100, 100, 255));
    ringShape.setPosition(100, 100); 

    float borderThickness = 20.0f;

    //ring edges
    topBorder.setSize(sf::Vector2f(width + borderThickness * 2, borderThickness));
    topBorder.setFillColor(sf::Color::Red);
    topBorder.setPosition(100 - borderThickness, 100 - borderThickness); 

    bottomBorder = topBorder;
    bottomBorder.setPosition(100 - borderThickness, 100 + height);

    leftBorder.setSize(sf::Vector2f(borderThickness, height + borderThickness * 2));
    leftBorder.setFillColor(sf::Color::Red);
    leftBorder.setPosition(100 - borderThickness, 100 - borderThickness); 

    rightBorder = leftBorder;
    rightBorder.setPosition(100 + width, 100 - borderThickness);
}

void Ring::draw(sf::RenderWindow& window) {
    window.draw(ringShape);
    window.draw(topBorder);
    window.draw(bottomBorder);
    window.draw(leftBorder);
    window.draw(rightBorder);
}

sf::FloatRect Ring::getBounds() const {
    //bounding ring
    sf::FloatRect bounds = ringShape.getGlobalBounds();

    bounds = sf::FloatRect(
        std::min(bounds.left, topBorder.getGlobalBounds().left),
        std::min(bounds.top, topBorder.getGlobalBounds().top),
        std::max(bounds.left + bounds.width, topBorder.getGlobalBounds().left + topBorder.getGlobalBounds().width) - std::min(bounds.left, topBorder.getGlobalBounds().left),
        std::max(bounds.top + bounds.height, topBorder.getGlobalBounds().top + topBorder.getGlobalBounds().height) - std::min(bounds.top, topBorder.getGlobalBounds().top)
    );

    bounds = sf::FloatRect(
        std::min(bounds.left, bottomBorder.getGlobalBounds().left),
        std::min(bounds.top, bottomBorder.getGlobalBounds().top),
        std::max(bounds.left + bounds.width, bottomBorder.getGlobalBounds().left + bottomBorder.getGlobalBounds().width) - std::min(bounds.left, bottomBorder.getGlobalBounds().left),
        std::max(bounds.top + bounds.height, bottomBorder.getGlobalBounds().top + bottomBorder.getGlobalBounds().height) - std::min(bounds.top, bottomBorder.getGlobalBounds().top)
    );

    bounds = sf::FloatRect(
        std::min(bounds.left, leftBorder.getGlobalBounds().left),
        std::min(bounds.top, leftBorder.getGlobalBounds().top),
        std::max(bounds.left + bounds.width, leftBorder.getGlobalBounds().left + leftBorder.getGlobalBounds().width) - std::min(bounds.left, leftBorder.getGlobalBounds().left),
        std::max(bounds.top + bounds.height, leftBorder.getGlobalBounds().top + leftBorder.getGlobalBounds().height) - std::min(bounds.top, leftBorder.getGlobalBounds().top)
    );

    bounds = sf::FloatRect(
        std::min(bounds.left, rightBorder.getGlobalBounds().left),
        std::min(bounds.top, rightBorder.getGlobalBounds().top),
        std::max(bounds.left + bounds.width, rightBorder.getGlobalBounds().left + rightBorder.getGlobalBounds().width) - std::min(bounds.left, rightBorder.getGlobalBounds().left),
        std::max(bounds.top + bounds.height, rightBorder.getGlobalBounds().top + rightBorder.getGlobalBounds().height) - std::min(bounds.top, rightBorder.getGlobalBounds().top)
    );

    return bounds;
}
