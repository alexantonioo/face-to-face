#include "Ring.hpp"

Ring::Ring(float width, float height) 
{
    ringShape.setSize(sf::Vector2f(width, height));
    ringShape.setFillColor(sf::Color(100, 100, 255));
    ringShape.setPosition(100, 100); 

    float borderThickness = 20.0f;

    // Bordes del ring
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
    sf::FloatRect ringBounds = ringShape.getGlobalBounds();
    
    // Incluir los bordes en los límites del ring
    sf::FloatRect topBounds = topBorder.getGlobalBounds();
    sf::FloatRect bottomBounds = bottomBorder.getGlobalBounds();
    sf::FloatRect leftBounds = leftBorder.getGlobalBounds();
    sf::FloatRect rightBounds = rightBorder.getGlobalBounds();
    
    float left = std::min({ringBounds.left, leftBounds.left});
    float top = std::min({ringBounds.top, topBounds.top});
    float right = std::max({ringBounds.left + ringBounds.width, rightBounds.left + rightBounds.width});
    float bottom = std::max({ringBounds.top + ringBounds.height, bottomBounds.top + bottomBounds.height});
    
    return sf::FloatRect(left, top, right - left, bottom - top);
}
