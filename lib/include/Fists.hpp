#pragma once
#include <string>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

class Fist {
public:

    Fist(bool isLeft = true);  
    void punch();  
    void update(float deltaTime, const sf::Vector2f& boxerPosition);  
    void draw(sf::RenderWindow& window);

    void startPunch(); 
    void resetPunch();
    
    bool isPunching() const;
    sf::FloatRect getHitbox() const;  

private:

    bool isLeft;
    sf::RectangleShape hitbox;  
    bool punching;             
    float punchDuration;        
    sf::Clock punchClock;       
};