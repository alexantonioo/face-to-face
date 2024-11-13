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

  initMenuOptions(1024, 768); 

    playWithBotCheckbox.setFont(font);
    playWithBotCheckbox.setString("[ ] Jugar con Bot");
    playWithBotCheckbox.setFillColor(sf::Color::White);
    playWithBotCheckbox.setPosition(1024/2, 768/2); // Ajusta según el diseño
    playWithBotCheckbox.setCharacterSize(30);
    
}


void Menu::initMenuOptions(float width, float height) {
    std::vector<std::string> options = {"Play", "Settings", "Exit",};
    menuOptions.resize(options.size());

    for (size_t i = 0; i < options.size(); ++i) {
        menuOptions[i].setFont(font);
        menuOptions[i].setString(options[i]);
        menuOptions[i].setFillColor(i == selectedOptionIndex ? sf::Color::Red : sf::Color::White);
        menuOptions[i].setPosition(sf::Vector2f(width / 2 - 50, height / (options.size() + 1) * (i + 1)));
        menuOptions[i].setCharacterSize(45);
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
        window.draw(playWithBotCheckbox);
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

            settingsMenu.handleInput(event);
            if (event.key.code == sf::Keyboard::Escape) {
                settingsSelected = false;  
            }
        } else {  

            if (event.key.code == sf::Keyboard::Up) moveUp();
            else if (event.key.code == sf::Keyboard::Down) moveDown();
            else if (event.key.code == sf::Keyboard::Enter) {
                if (selectedOptionIndex == 0) {  
                    startSelected = true;  
                } else if (selectedOptionIndex == 1) {  
                    settingsSelected = true;  
                } else if (selectedOptionIndex == 2) {  
                    window.close();  
                }
            }
        }
    }
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if (playWithBotCheckbox.getGlobalBounds().contains(mousePos.x, mousePos.y)) {
            playWithBot = !playWithBot;
            playWithBotCheckbox.setString(playWithBot ? "[X] Jugar con Bot" : "[ ] Jugar con Bot");
        }
    }
}


bool Menu::isSettingsSelected() const {
    return settingsSelected;
}

bool Menu::isPlayWithBotEnabled() const {
    return playWithBot;
}

