#include "Menu.hpp"
#include <iostream>

Menu::Menu() {
    // Fuente
  

    if (!font.loadFromFile("../../assets/fonts/Eight-Bit-Madness.ttf")) {
        std::cerr << "Error 'assets/fonts/Eight-Bit-Madness.ttf'" << std::endl;
    }


    // fondo
    /*if (!backgroundTexture.loadFromFile("/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/backgroundmenu.png")) {
        std::cerr << "Error: No se pudo cargar la imagen de fondo." << std::endl;
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }*/

  initMenuOptions(800, 600);  // Cambia el tamaño de la ventana según tu configuración
    
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
    //window.draw(backgroundSprite);
    for (const auto& option : menuOptions) {
        window.draw(option);
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

void Menu::handleInput(const sf::Event& event, sf::RenderWindow& window) 
{
    if (event.type == sf::Event::KeyPressed) 
    {
        if (event.key.code == sf::Keyboard::Up) moveUp();
        else if (event.key.code == sf::Keyboard::Down) moveDown();
        else if (event.key.code == sf::Keyboard::Enter) 
        {
            if (selectedOptionIndex == 0) 
            { 
                startSelected = true;
            } 
            else if (selectedOptionIndex == 2) 
            { 
                window.close(); // close game
            }
        }
    }
}
