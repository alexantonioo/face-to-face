#include <SFML/Graphics.hpp>
#include "Boxer.hpp"
#include "Ring.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Boxing Game");

    // Inicializar el ring
    Ring ring(700, 500); // Ajusta el tamaño según tus necesidades

    // Inicializar los boxeadores
    Boxer boxer1(sf::Color::Red); // Usar el constructor que acepta color
    Boxer boxer2(sf::Color::Blue); // Usar el constructor que acepta color

    // Configurar la posición de los boxeadores
    boxer1.setPosition(300.0f, 300.0f); // Posición del boxeador 1
    boxer2.setPosition(400.0f, 300.0f); // Posición del boxeador 2

    // Bucle principal
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Manejar controles
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            boxer1.move(-1.0f, 0.0f); // Mover a la izquierda
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            boxer1.move(1.0f, 0.0f); // Mover a la derecha
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            boxer2.move(-1.0f, 0.0f); // Mover a la izquierda (boxeador 2)
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            boxer2.move(1.0f, 0.0f); // Mover a la derecha (boxeador 2)
        }

        // Limpiar la ventana
        window.clear(sf::Color::Black);
        
        // Dibujar el ring y los boxeadores
        ring.draw(window);
        boxer1.draw(window); // Método que necesitas definir en Boxer para dibujar
        boxer2.draw(window); // Método que necesitas definir en Boxer para dibujar

        // Mostrar en la ventana
        window.display();
    }

    return 0;
}
