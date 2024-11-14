#include "SettingsMenu.hpp"
#include "Path.hpp"
#include <iostream>

SettingsMenu::SettingsMenu() {
    if (!font.loadFromFile(Path::BITM_FONT_PATH)) {
        std::cerr << "Error 'assets/fonts/Eight-Bit-Madness.ttf'" << std::endl;
    }

    std::vector<std::string> maps = {"Ring", "Street"};
    mapOptions.resize(maps.size());

    for (size_t i = 0; i < maps.size(); ++i) {
        mapOptions[i].setFont(font);
        mapOptions[i].setString(maps[i]);
        mapOptions[i].setFillColor(i == selectedMapIndex ? sf::Color::Red : sf::Color::White);
        mapOptions[i].setPosition(400, 200 + static_cast<float>(i) * 50);
        mapOptions[i].setCharacterSize(30);
    }
}

void SettingsMenu::draw(sf::RenderWindow& window) {
    for (const auto& option : mapOptions) {
        window.draw(option);
    }
}

void SettingsMenu::handleInput(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Up) {
            moveUp();
        } 
        else if (event.key.code == sf::Keyboard::Down) {
            moveDown();
        } 
        else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Right) {
            // Alternar entre opciones de escenario (ring y street)
            selectedMapIndex = (selectedMapIndex == 0) ? 1 : 0;
        }
        else if (event.key.code == sf::Keyboard::Escape) {
            selectedMapIndex = -1; // Puede usarse para salir de la configuración
        }
    }
}


void SettingsMenu::moveUp() {
    if (selectedMapIndex > 0) {
        mapOptions[selectedMapIndex].setFillColor(sf::Color::White);
        selectedMapIndex--;
        mapOptions[selectedMapIndex].setFillColor(sf::Color::Red);
    }
}

void SettingsMenu::moveDown() {
    if (selectedMapIndex < mapOptions.size() - 1) {
        mapOptions[selectedMapIndex].setFillColor(sf::Color::White);
        selectedMapIndex++;
        mapOptions[selectedMapIndex].setFillColor(sf::Color::Red);
    }
}

/*std::string SettingsMenu::getSelectedMap() const {
    return selectedMapIndex >= 0 ? mapOptions[selectedMapIndex].getString() : "None";
}*/

int SettingsMenu::getSelectedMapIndex() const {
    return selectedMapIndex;
}

void SettingsMenu::setSelectedMapIndex(int index) {
    selectedMapIndex = index;
}