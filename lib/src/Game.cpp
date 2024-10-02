#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Ring.hpp"
#include "Boxer.hpp"


Game::Game() 
    : window(sf::VideoMode(800, 600), "Face to Face - Boxing Ring"), 
      boxer1("Boxer 1", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/boxer.png"), 
      boxer2("Boxer 2", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/boxer.png"), 
      ring(400, 400) 
{
    boxer1.setPosition(100, 100);  // Posición inicial
    boxer2.setPosition(600, 600);  // Posición inicial

    // Cargar texturas y animaciones
    boxer1.loadTexture("default ", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/boxer.png");  // Textura inicial
    boxer2.loadTexture("default", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/boxer.png");

   /* boxer1.loadAnimation("jab", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/right_jab.png");  // Animación de jab
    boxer1.loadAnimation("hook", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/hook.png");  // Animación de hook

    
    boxer2.loadAnimation("jab", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/right_jab.png");
    boxer2.loadAnimation("hook", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/hook.png");*/
}


/*//test
// Cargar el boxeador 1 con su textura inicial
    boxer1 = new Boxer("Player1", "assets/images/boxer.png");
    // Cargar animaciones adicionales
    boxer1 ->loadTexture("jab", "assets/images/boxer_jab.png");
    boxer1 ->loadTexture("hook", "assets/images/boxer_hook.png");

    // Cargar el boxeador 2 con su textura inicial
    boxer2 = new Boxer("Player2", "assets/images/boxer.png");
    // Cargar animaciones adicionales para boxer2
    boxer2 ->loadTexture("jab", "assets/images/boxer_jab.png");
    boxer2 ->loadTexture("hook", "assets/images/boxer_hook.png");

*/

void Game::run() 
{
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // boxer 1 movement wasd
        sf::Vector2f movement1(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        {
            movement1.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) 
        {
            movement1.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {
            movement1.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
        {
            movement1.x += 1.0f;
        }

        boxer1.move(movement1);

        // boxer 2 movement arrows
        sf::Vector2f movement2(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) 
        {
            movement2.y -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) 
        {
            movement2.y += 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
        {
            movement2.x -= 1.0f;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
            movement2.x += 1.0f;
        }

        boxer2.move(movement2);

        handleCollisions();

        // draw averything
        window.clear(sf::Color::Black);
        ring.draw(window);
        boxer1.draw(window);
        boxer2.draw(window);
        window.display();
    }
}

void Game::handleCollisions() 
{
    sf::FloatRect boxer1Bounds = boxer1.getBounds();
    sf::FloatRect boxer2Bounds = boxer2.getBounds();
    sf::FloatRect ringBounds = ring.getBounds();

    // Collisions ring
    if (boxer1Bounds.left < ringBounds.left) 
    {
        boxer1.setPosition(ringBounds.left, boxer1Bounds.top);
    }
    if (boxer1Bounds.left + boxer1Bounds.width > ringBounds.left + ringBounds.width) 
    {
        boxer1.setPosition(ringBounds.left + ringBounds.width - boxer1Bounds.width, boxer1Bounds.top);
    }
    if (boxer1Bounds.top < ringBounds.top) 
    {
        boxer1.setPosition(boxer1Bounds.left, ringBounds.top);
    }
    if (boxer1Bounds.top + boxer1Bounds.height > ringBounds.top + ringBounds.height) 
    {
        boxer1.setPosition(boxer1Bounds.left, ringBounds.top + ringBounds.height - boxer1Bounds.height);
    }

    if (boxer2Bounds.left < ringBounds.left) 
    {
        boxer2.setPosition(ringBounds.left, boxer2Bounds.top);
    }
    if (boxer2Bounds.left + boxer2Bounds.width > ringBounds.left + ringBounds.width) 
    {
        boxer2.setPosition(ringBounds.left + ringBounds.width - boxer2Bounds.width, boxer2Bounds.top);
    }
    if (boxer2Bounds.top < ringBounds.top) {
        boxer2.setPosition(boxer2Bounds.left, ringBounds.top);
    }
    if (boxer2Bounds.top + boxer2Bounds.height > ringBounds.top + ringBounds.height) 
    {
        boxer2.setPosition(boxer2Bounds.left, ringBounds.top + ringBounds.height - boxer2Bounds.height);
    }

    // Collisions between boxers
    if (boxer1Bounds.intersects(boxer2Bounds)) 
    {
        sf::FloatRect intersection;
        boxer1Bounds.intersects(boxer2Bounds, intersection);

        sf::Vector2f moveDirection(0, 0);
        
        if (intersection.width < intersection.height) 
        {
            if (boxer1Bounds.left < boxer2Bounds.left) 
            {
                moveDirection.x = -intersection.width / 2;
            } else 
            {
                moveDirection.x = intersection.width / 2;
            }
        }
         else 
        {
            if (boxer1Bounds.top < boxer2Bounds.top) 
            {
                moveDirection.y = -intersection.height / 2;
            } 
            else 
            {
                moveDirection.y = intersection.height / 2;
            }
        }

        boxer1.move(moveDirection);
        boxer2.move(-moveDirection);  
    }
}
