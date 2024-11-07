#include <SFML/Graphics.hpp>
#include "Boxer.hpp"
#include "Ring.hpp"
#include "Menu.hpp"
#include "Collision.hpp"
class Game {
public:
    Game();
    void run();
    void drawHearts(const Boxer& boxer, const sf::Vector2f& position); 

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
    Collision hitbox_boxer1;
    Collision hitbox_boxer2;
    void draw();
    void drawHearts();

    };
