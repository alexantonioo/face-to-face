#include "Menu.hpp"

Menu::Menu(sf::RenderWindow& window): window(window)  /*selectedOptionIndex(0)*/ {
    // Cargar la fuente
    if (!font.loadFromFile("path/to/your/font.ttf")) {
        // Manejar error si no se carga la fuente
    }
    //initMenuOptions(width, height);
}

void Menu::initMenuOptions(float width, float height) {
    std::vector<std::string> options = {"Play", "Settings", "Exit"};
    menuOptions.resize(options.size());

    for (size_t i = 0; i < options.size(); ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(options[i]);
        menuOptions[i].setFillColor(i == selectedOptionIndex ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setPosition(sf::Vector2f(width / 2, height / (options.size() + 1) * (i + 1)));
        menuOptions[i].setCharacterSize(30);
        menuOptions[i].setStyle(sf::Text::Bold);
    }
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
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



void Menu::draw() 
{
    window.clear();
    window.draw(startButton);
    // Dibujar otros elementos del menú
    window.display();
}

bool Menu::isStartSelected() const 
{
    return startSelected;
}