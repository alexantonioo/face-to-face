// lib/src/Ring.cpp
#include "Ring.hpp"

Ring::Ring(float width, float height) {
    // Configuración del ring y sus bordes (como se hizo antes)
    ringShape.setSize(sf::Vector2f(width, height));
    ringShape.setFillColor(sf::Color(100, 100, 255));
    ringShape.setPosition(100, 100);

    float borderThickness = 20.0f;

    // Borde superior
    topBorder.setSize(sf::Vector2f(width + borderThickness * 2, borderThickness));
    topBorder.setFillColor(sf::Color::Red);
    topBorder.setPosition(100 - borderThickness, 100 - borderThickness);

    // Borde inferior
    bottomBorder = topBorder;
    bottomBorder.setPosition(100 - borderThickness, 100 + height);

    // Borde izquierdo
    leftBorder.setSize(sf::Vector2f(borderThickness, height + borderThickness * 2));
    leftBorder.setFillColor(sf::Color::Red);
    leftBorder.setPosition(100 - borderThickness, 100 - borderThickness);

    // Borde derecho
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
    return ringShape.getGlobalBounds();
}
