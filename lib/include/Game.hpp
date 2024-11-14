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
    

    enum BackgroundType { 
        RING,
        STREET 
    };
    void setBackground(BackgroundType backgroundType);
    void setBotActive(bool active);

    
private:

    sf::RenderWindow window;
    sf::Clock clock;
    Menu menu;

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    BackgroundType currentBackground = RING;  // Por defecto al iniciar 
    int selectedMapIndex = 0;

    sf::Texture ringTexture_;
    sf::Texture streetTexture_;
    sf::Sprite ringSprite_;
    sf::Sprite streetSprite_;

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
    Collision hitbox_ring;
    void draw();
    void drawHearts();

    bool isBotActive;
    bool isGameOver;
    sf::Text gameOverText;
    sf::Font font;

    };
