#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Ring.hpp"
#include "Boxer.hpp"
//#include "Menu.hpp"


Game::Game() 
    : window(sf::VideoMode(1024, 768), "Face to Face", sf::Style::Titlebar | sf::Style::Close), 
    
      menu(window),
      currentState(MENU),
      boxer1("Boxer 1", "../../assets/images/boxer.png"), 
      boxer2("Boxer 2", "../../assets/images/boxer2.png"), 
      ring(800.0f, 600.0f, "../../assets/images/ring.png")
      
{
    boxer1.setPosition(100, 100);  
    boxer2.setPosition(600, 600);  

    boxer1.loadTexture("default ", "../../assets/images/boxer.png");  
    boxer2.loadTexture("default","../../assets/images/boxer2.png");

}

void Game::run() 
{
    bool isPaused = false;
    sf::Clock deltaClock;
    const float targetFPS = 60.0f;
    const float targetFrameTime = 1.0f / targetFPS;

    window.setVerticalSyncEnabled(true);
    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){
                    isPaused = !isPaused;
                }

            if (isPaused){
                menu.handleInput(event, window);
            }

            if (currentState == MENU) {
                menu.handleInput(event, window);
                if (menu.isStartSelected()) {
                    currentState = PLAYING;
                }

        float frameTime = clock.restart().asSeconds();
        boxer1.updatefps(frameTime);
        boxer2.updatefps(frameTime);

        // Limitar los FPS a 60
        if (frameTime < targetFrameTime) 
        {
            sf::sleep(sf::seconds(targetFrameTime - frameTime));
        }
            
        }
 }
   
    
    window.clear(sf::Color::Black);
        
        switch (currentState) {
            case MENU:
                menu.draw(window);
                break;

            case PLAYING:
                handleInput();
                update();

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
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) 
        {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
        {
        boxer2.dodge(sf::Vector2f(-1.f, 0.f)); // Esquivar hacia la izquierda
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
        boxer2.dodge(sf::Vector2f(1.f, 0.f)); // Esquivar hacia la derecha
        }
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

        //DODGE BOXER 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
        {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {
        boxer1.dodge(sf::Vector2f(-0.5f, 0.f)); 
        }   
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))               
        {
        boxer1.dodge(sf::Vector2f(0.5f, 0.f)); 
        }   
        }               

                boxer1.handleInput(sf::Keyboard::Key::R, sf::Keyboard::Key::T, sf::Keyboard::Key::Y, sf::Keyboard::Key::U);
                boxer2.handleInput(sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::J); 
            
                boxer1.update(boxer2.getSprite().getPosition());
                boxer2.update(boxer1.getSprite().getPosition());
                if (isPaused) 
                {
                    menu.draw(window); 
                }
                else {
                handleCollisions();

                ring.draw(window);
                boxer1.draw(window);
                boxer2.draw(window);
                break;
                }
        }
    
        window.display();
        
    }
}

void Game::draw() {
    window.clear();

    // Configura las posiciones de las barras
    boxer1.staminaBar.setPosition(10, 10); 
    boxer2.staminaBar.setPosition(window.getSize().x - 110, 10); 

    boxer1.updateStaminaBar();
    boxer2.updateStaminaBar();

    //hearts
    drawHearts(boxer1, sf::Vector2f(50, 10));         
    drawHearts(boxer2, sf::Vector2f(600, 10));      

    boxer1.draw(window);
    boxer2.draw(window);
    window.draw(boxer1.staminaBar);
    window.draw(boxer2.staminaBar);
    
    window.display();
}



void Game::drawHearts(const Boxer& boxer, const sf::Vector2f& position) 
    {

    static sf::Texture heartTexture;
    static bool textureLoaded = false;
    if (!textureLoaded) {
        if (!heartTexture.loadFromFile("../../assets/images/hearts.png")) {
            
            return;
        }
        textureLoaded = true;
    }
    sf::Sprite heartSprite(heartTexture);
    for (int i = 0; i < boxer.get_hearts(); ++i) {
        heartSprite.setPosition(position.x + i * (heartSprite.getGlobalBounds().width + 5), position.y);
        window.draw(heartSprite);
    }
}


void Game::handleCollisions() 
{
    sf::FloatRect boxer1Bounds = boxer1.getSprite().getGlobalBounds();
    sf::FloatRect boxer2Bounds = boxer2.getSprite().getGlobalBounds();
    sf::FloatRect ringBounds = ring.getBounds();

    // boxer 1 ring collisions
    if (boxer1Bounds.left < ringBounds.left) {
        boxer1.move({ringBounds.left - boxer1Bounds.left, 0});
    }
    if (boxer1Bounds.left + boxer1Bounds.width > ringBounds.left + ringBounds.width) {
        boxer1.move({ringBounds.left + ringBounds.width - (boxer1Bounds.left + boxer1Bounds.width), 0});
    }
    if (boxer1Bounds.top < ringBounds.top) {
        boxer1.move({0, ringBounds.top - boxer1Bounds.top});
    }
    if (boxer1Bounds.top + boxer1Bounds.height > ringBounds.top + ringBounds.height) {
        boxer1.move({0, ringBounds.top + ringBounds.height - (boxer1Bounds.top + boxer1Bounds.height)});
    }

    // boxer 2 ring collisions
    if (boxer2Bounds.left < ringBounds.left) {
        boxer2.move({ringBounds.left - boxer2Bounds.left, 0});
    }
    if (boxer2Bounds.left + boxer2Bounds.width > ringBounds.left + ringBounds.width) {
        boxer2.move({ringBounds.left + ringBounds.width - (boxer2Bounds.left + boxer2Bounds.width), 0});
    }
    if (boxer2Bounds.top < ringBounds.top) {
        boxer2.move({0, ringBounds.top - boxer2Bounds.top});
    }
    if (boxer2Bounds.top + boxer2Bounds.height > ringBounds.top + ringBounds.height) {
        boxer2.move({0, ringBounds.top + ringBounds.height - (boxer2Bounds.top + boxer2Bounds.height)});
    }


    boxer1.update(boxer2.getSprite().getPosition());
    boxer2.update(boxer1.getSprite().getPosition());


    // collisions between boxers
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


     if (boxer1Bounds.intersects(boxer2Bounds)) 
    {
        sf::FloatRect intersection;
        boxer1Bounds.intersects(boxer2Bounds, intersection);

        
        if (boxer1.getState() == BoxerState::ATTACKING) 
        {
            boxer2.receivePunch(); 
        }

        if (boxer2.getState() == BoxerState::ATTACKING) 
        {
            boxer1.receivePunch(); 
        }
    }
}

void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (currentState == GameState::MENU) {
            menu.handleInput(event, window);
        }
    }
}

void Game::update() {
    if (currentState == GameState::MENU) {
        menu.update();
    }
}

void Game::render() {
    window.clear();
    
    if (currentState == GameState::MENU) {
        menu.draw(window); 
    } else {
        
    }

    window.display();
}