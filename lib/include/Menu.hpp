#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "SettingsMenu.hpp"


class Menu {
public:
    Menu(sf::RenderWindow& window);  

    //Menu(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    int getSelectedOption() const;
    bool isStartSelected() const;
    bool isSettingsSelected() const;
    void resetStartSelected();

private:
    std::vector<sf::Text> menuOptions;
    sf::Font font;
    sf::RectangleShape startButton, settingsButton, exitButton;
    int selectedOptionIndex = 0;
    bool startSelected = false;
    bool settingsSelected = false;
    //fondo
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    void setupButtons();
    void initMenuOptions(float width, float height);
    void moveUp();
    void moveDown();

    SettingsMenu settingsMenu;
};
