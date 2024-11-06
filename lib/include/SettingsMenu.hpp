#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class SettingsMenu {
public:
    SettingsMenu();
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event);

    std::string getSelectedMap() const;

private:
    std::vector<sf::Text> mapOptions;
    sf::Font font;
    int selectedMapIndex = 0;
    void moveUp();
    void moveDown();
};
