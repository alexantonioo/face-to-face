#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Menu {
public:
    Menu();  

    //Menu(sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    void handleInput(const sf::Event& event, sf::RenderWindow& window);
    int getSelectedOption() const;
    bool isStartSelected() const;

private:
    std::vector<sf::Text> menuOptions;
    sf::Font font;
    sf::RectangleShape startButton, settingsButton, exitButton;
    int selectedOptionIndex = 0;
    bool startSelected = false;

    void setupButtons();
    void initMenuOptions(float width, float height);
    void moveUp();
    void moveDown();
};
