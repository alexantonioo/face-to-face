#include "Menu.hpp"
#include <iostream>

Menu::Menu(sf::RenderWindow& window) {
    // Fuente
    if (!font.loadFromFile("/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/fonts/Eight-Bit Madness.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente desde 'assets/fonts/arial.ttf'" << std::endl;
    }
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

void Menu::setupButtons() {
    startButton.setSize(sf::Vector2f(150, 50));
    startButton.setPosition(325, 200);
    startButton.setFillColor(sf::Color::Red);

    settingsButton.setSize(sf::Vector2f(150, 50));
    settingsButton.setPosition(325, 300);
    settingsButton.setFillColor(sf::Color::White);

    exitButton.setSize(sf::Vector2f(150, 50));
    exitButton.setPosition(325, 400);
    exitButton.setFillColor(sf::Color::White);
}

void Menu::draw(sf::RenderWindow& window) {
    for (const auto& option : menuOptions) {
        window.draw(option);
    }
    window.draw(startButton);
    window.draw(settingsButton);
    window.draw(exitButton);
}

void Menu::update() {
    // Aquí puedes incluir lógica de actualización específica del menú si es necesario
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
        if (event.key.code == sf::Keyboard::Up) moveUp();
        else if (event.key.code == sf::Keyboard::Down) moveDown();
        else if (event.key.code == sf::Keyboard::Enter) startSelected = (selectedOptionIndex == 0);
    }
    else if (event.type == sf::Event::MouseButtonPressed) {
        if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
            startSelected = true;
        }
    }
}
