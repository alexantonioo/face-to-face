// lib/include/Game.hpp
#define GAME_HPP

#include "Boxer.hpp"
#include "Ring.hpp"

class Game {
public:
    // Constructor del juego
    Game();

    // Función principal para ejecutar el ciclo del juego
    void run();

private:
    sf::RenderWindow window;  // Ventana del juego

    // Dos boxeadores
    Boxer boxer1;
    Boxer boxer2;

    Ring ring;  // El ring del juego

    // Función para manejar colisiones entre los boxeadores y el ring
    void handleCollisions();
};

