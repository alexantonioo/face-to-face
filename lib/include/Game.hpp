<<<<<<< Updated upstream
=======
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
    void update();
    void draw();  
};

>>>>>>> Stashed changes
