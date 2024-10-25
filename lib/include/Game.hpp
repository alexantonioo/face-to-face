#include "Boxer.hpp"
#include "Ring.hpp"

class Game {
public:
    Game();
    void run();

private:
    sf::RenderWindow window; 

    Boxer boxer1;
    Boxer boxer2;
    Ring ring;  

    void handleCollisions();
    void update();  // update boxer 
    void draw();

};
