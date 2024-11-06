#include <SFML/Graphics.hpp>
#include "Menu.hpp"
#include "SettingsMenu.hpp"
#include <iostream>


Menu::Menu(sf::RenderWindow& window){

    if (!font.loadFromFile("../../assets/fonts/Eight-Bit-Madness.ttf")) {
        std::cerr << "Error 'assets/fonts/Eight-Bit-Madness.ttf'" << std::endl;
    }


    if (!backgroundTexture.loadFromFile("../../assets/images/backgroundmenu.png")) {
        std::cerr << "Error al cargar la imagen de fondo" << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture); 
    }

    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = backgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);

  initMenuOptions(800, 600); 
    
}


void Menu::initMenuOptions(float width, float height) {
    std::vector<std::string> options = {"Play", "Settings", "Exit"};
    menuOptions.resize(options.size());

    for (size_t i = 0; i < options.size(); ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(options[i]);
        menuOptions[i].setFillColor(i == selectedOptionIndex ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setPosition(sf::Vector2f(width / 2 - 50, height / (options.size() + 1) * (i + 1)));
        menuOptions[i].setCharacterSize(30);
        menuOptions[i].setStyle(sf::Text::Bold);
    }
}


void Menu::draw(sf::RenderWindow& window) {
    //fondo
    window.draw(backgroundSprite);

    if (settingsSelected) {  
        settingsMenu.draw(window);  
    } else {
        for (const auto& option : menuOptions) {
            window.draw(option);
        }
    }
}

void Menu::update() {
    
}

void Menu::moveUp() {
    if (selectedOptionIndex > 0) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex--;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

void Menu::moveDown() {
    if (selectedOptionIndex < menuOptions.size() - 1) {
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::White);
        selectedOptionIndex++;
        menuOptions[selectedOptionIndex].setFillColor(sf::Color::Red);
    }
}

int Menu::getSelectedOption() const {
    return selectedOptionIndex;
}

bool Menu::isStartSelected() const {
    return startSelected;
}

void Menu::handleInput(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::KeyPressed) {
        if (settingsSelected) {  
            // Si está en el submenú de configuración, se maneja la entrada en `settingsMenu`.
            settingsMenu.handleInput(event);
            if (event.key.code == sf::Keyboard::Escape) {
                settingsSelected = false;  // Salir del submenú al presionar Escape.
            }
        } else {  
            // Maneja la entrada en el menú principal.
            if (event.key.code == sf::Keyboard::Up) moveUp();
            else if (event.key.code == sf::Keyboard::Down) moveDown();
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedOptionIndex == 0) {  
                    startSelected = true;  // Señala que se seleccionó "Play".
                } else if (selectedOptionIndex == 1) {  
                    settingsSelected = true;  // Entra al submenú de configuración.
                } else if (selectedOptionIndex == 2) {  
                    window.close();  // Cierra el juego si se selecciona "Exit".
                }
            }
        }
    }
}

/*void Menu::resetStartSelected() {
    startSelected = false;
}*/

bool Menu::isSettingsSelected() const {
    return settingsSelected;
}