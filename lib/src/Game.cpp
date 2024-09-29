// lib/src/Game.cpp
#include "Game.hpp"
#include <SFML/Window.hpp>

Game::Game() 
    : window(sf::VideoMode(800, 600), "Face to Face - Boxing Ring"), 
      boxer1(sf::Color::Red), 
      boxer2(sf::Color::Blue), 
      ring(400, 400) 
{
    boxer1.setPosition(150, 150);  // Posición inicial del boxeador 1
    boxer2.setPosition(450, 450);  // Posición inicial del boxeador 2
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Movimiento del boxeador 1 (controlado con WASD)
        sf::Vector2f movement1(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            movement1.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            movement1.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            movement1.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            movement1.x += 1.0f;
        }

        boxer1.move(movement1);

        // Movimiento del boxeador 2 (controlado con flechas del teclado)
        sf::Vector2f movement2(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
            movement2.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
            movement2.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            movement2.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            movement2.x += 1.0f;
        }

        boxer2.move(movement2);

        // Manejar colisiones
        handleCollisions();

        // Dibujar todo
        window.clear(sf::Color::Black);
        ring.draw(window);
        boxer1.draw(window);
        boxer2.draw(window);
        window.display();
    }
}

void Game::handleCollisions() {
    sf::FloatRect boxer1Bounds = boxer1.getBounds();
    sf::FloatRect boxer2Bounds = boxer2.getBounds();
    sf::FloatRect ringBounds = ring.getBounds();

    // Colisiones con los límites del ring para ambos boxeadores
    if (boxer1Bounds.left < ringBounds.left) {
        boxer1.setPosition(ringBounds.left, boxer1Bounds.top);
    }
    if (boxer1Bounds.left + boxer1Bounds.width > ringBounds.left + ringBounds.width) {
        boxer1.setPosition(ringBounds.left + ringBounds.width - boxer1Bounds.width, boxer1Bounds.top);
    }
    if (boxer1Bounds.top < ringBounds.top) {
        boxer1.setPosition(boxer1Bounds.left, ringBounds.top);
    }
    if (boxer1Bounds.top + boxer1Bounds.height > ringBounds.top + ringBounds.height) {
        boxer1.setPosition(boxer1Bounds.left, ringBounds.top + ringBounds.height - boxer1Bounds.height);
    }

    if (boxer2Bounds.left < ringBounds.left) {
        boxer2.setPosition(ringBounds.left, boxer2Bounds.top);
    }
    if (boxer2Bounds.left + boxer2Bounds.width > ringBounds.left + ringBounds.width) {
        boxer2.setPosition(ringBounds.left + ringBounds.width - boxer2Bounds.width, boxer2Bounds.top);
    }
    if (boxer2Bounds.top < ringBounds.top) {
        boxer2.setPosition(boxer2Bounds.left, ringBounds.top);
    }
    if (boxer2Bounds.top + boxer2Bounds.height > ringBounds.top + ringBounds.height) {
        boxer2.setPosition(boxer2Bounds.left, ringBounds.top + ringBounds.height - boxer2Bounds.height);
    }

    // Colisiones entre los dos boxeadores
    if (boxer1Bounds.intersects(boxer2Bounds)) {
        // Lógica para empujar a los boxeadores fuera de la intersección
        if (boxer1Bounds.left < boxer2Bounds.left) {
            boxer1.setPosition(boxer1Bounds.left - 1.0f, boxer1Bounds.top);
            boxer2.setPosition(boxer2Bounds.left + 1.0f, boxer2Bounds.top);
        } else {
            boxer1.setPosition(boxer1Bounds.left + 1.0f, boxer1Bounds.top);
            boxer2.setPosition(boxer2Bounds.left - 1.0f, boxer2Bounds.top);
        }
    }
}
