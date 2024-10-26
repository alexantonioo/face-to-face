#include <SFML/Graphics.hpp>
#include "Boxer.hpp"
#include "Ring.hpp"
#include "Menu.hpp"

class Game {
public:
    Game();
    void run();

private:

    sf::RenderWindow window;
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

    };