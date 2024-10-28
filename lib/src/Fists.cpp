#include "Game.hpp"
#include "Fists.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>

Fist::Fist(bool isLeft)
    : punching(false), punchDuration(0.2f) {
    hitbox.setSize(sf::Vector2f(20, 10));  // Tamaño de la hitbox del puño
    hitbox.setFillColor(sf::Color::Red);   

    if (isLeft) {
        hitbox.setPosition(-30, 0);  
    } else {
        hitbox.setPosition(30, 0);
    }
}

void Fist::punch() {
    punching = true;
    punchClock.restart();  
}

void Fist::update(float deltaTime, const sf::Vector2f& boxerPosition) {
    
    hitbox.setPosition(boxerPosition + hitbox.getPosition());

   
    if (punching && punchClock.getElapsedTime().asSeconds() > punchDuration) {
        punching = false;
    }
}

void Fist::draw(sf::RenderWindow& window) {
    if (punching) {
        window.draw(hitbox);
    }
}

bool Fist::isPunching() const {
    return punching;
}

void Fist::startPunch() {
    punching = true; 
}

sf::FloatRect Fist::getHitbox() const {
    return hitbox.getGlobalBounds();
}