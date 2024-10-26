#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
Menu();
    Menu(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);
    void moveUp();
    void moveDown();
    int getSelectedOption() const;

    void handleInput(const sf::Event& event);

    void draw();
    bool isStartSelected() const;

private:
    std::vector<sf::Text> menuOptions;
    int selectedOptionIndex;
    sf::Font font;


 sf::RenderWindow& window;


    sf::RectangleShape startButton;
    sf::RectangleShape settingsButton;
    sf::RectangleShape exitButton;

    bool startSelected = false;

    void setupButtons();

    void initMenuOptions(float width, float height);
};

