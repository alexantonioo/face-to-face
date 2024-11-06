#include <SFML/Graphics.hpp>
#include "Boxer.hpp"
#include "Ring.hpp"
#include "Menu.hpp"

class Game {
public:
    Game();
    void run();
    void drawHearts(const Boxer& boxer, const sf::Vector2f& position); 
    void limitFPS(float targetFPS = 30.0f);
private:

    sf::RenderWindow window;
    sf::Clock clock;
    Menu menu;

    void handleCollisions();
    void update();
    void render();
    void handleInput();

    enum GameState {
        MENU,
        PLAYING
    };

    void showMenu();
    void processMenuEvents();
    bool isInMenu = true; 

    GameState currentState;  
    Boxer boxer1;
    Boxer boxer2;
    Ring ring;
    void draw();
    void drawHearts();

    };
