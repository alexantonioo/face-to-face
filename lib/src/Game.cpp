#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Ring.hpp"
#include "Boxer.hpp"
#include "Collision.hpp"
#include <iostream>
#include "SettingsMenu.hpp"



Game::Game() 
    : window(sf::VideoMode(1024, 768), "Face to Face", sf::Style::Titlebar | sf::Style::Close), 
    
      isGameOver(false),
      menu(window),
      currentState(MENU),
      currentBackground(STREET),
      boxer1("Boxer 1", "../../assets/images/idle_red.png",sf::Vector2f(512, 120)), 
      boxer2("Boxer 2", "../../assets/images/idle_blue.png",sf::Vector2f(512, 440)), 
      ring(800.0f, 600.0f, "../../assets/images/ring.png"),
      hitbox_boxer1(sf::Vector2f(512 - 5, 120 + 10), sf::Vector2f(05, 05)),
      hitbox_boxer2(sf::Vector2f(512 - 5, 440 + 10), sf::Vector2f(05, 05)),
      hitbox_ring(sf::Vector2f(1024 / 2.0f, 768 / 2.0f), sf::Vector2f(800.0f, 700.0f)),
      
      
      isBotActive(false)
{
   
if (!font.loadFromFile("../../assets/fonts/Eight-Bit-Madness.ttf")) {  // Carga la fuente
        // Manejo de error si la fuente no se carga
    }

gameOverText.setFont(font); 
gameOverText.setString("Game Over");
gameOverText.setCharacterSize(50);
gameOverText.setFillColor(sf::Color::Red);
gameOverText.setStyle(sf::Text::Bold);
gameOverText.setPosition(400, 300);


if (!ringTexture_.loadFromFile("../../assets/images/ring.png")) 
{
        std::cerr << "Error al cargar la textura del ring" << std::endl;
    } else {
        ringSprite_.setTexture(ringTexture_);
        ringSprite_.setScale(
            window.getSize().x / static_cast<float>(ringTexture_.getSize().x),
            window.getSize().y / static_cast<float>(ringTexture_.getSize().y)
        );
    }

    // street texture
    if (!streetTexture_.loadFromFile("../../assets/images/street.png")) {
        std::cerr << "Error al cargar la textura de la calle" << std::endl;
    } else {
        streetSprite_.setTexture(streetTexture_);
        streetSprite_.setScale(
            window.getSize().x / static_cast<float>(streetTexture_.getSize().x),
            window.getSize().y / static_cast<float>(streetTexture_.getSize().y)
        );
    }
    setBackground(STREET);


    boxer1.loadTexture("default", "../../assets/images/boxer.png");  // Textura inicial
    boxer2.loadTexture("default", "../../assets/images/boxer.png");
    

    boxer1.vector = boxer2.getSprite().getPosition() - boxer1.getSprite().getPosition();
    boxer1.vector = boxer1.getSprite().getPosition() - boxer2.getSprite().getPosition();

}

void Game::run() 
{
    bool isPaused = false;
    sf::Clock deltaClock;
    const float targetFPS = 60.0f;
    const float targetFrameTime = 1.0f / targetFPS;
    window.setFramerateLimit(120);
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
                if (menu.isStartSelected()) 
                {   
                        if(menu.isPlayWithBotEnabled())
                        {
                            setBotActive(true);
                        }
                        else if (menu.isPlayWithBotEnabled())
                        {
                            setBotActive(false);
                        }
                    setBackground(static_cast<BackgroundType>(menu.getSelectedOption()));
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
        //block
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::K))
        
        //Dodge
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::U)) 
        {

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) 
        {
        boxer2.dodge(sf::Vector2f(-1.f, 0.f)); 
        } 
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) 
        {
        boxer2.dodge(sf::Vector2f(1.f, 0.f)); 
        }
        }

        boxer1.move(movement1);
        hitbox_boxer1.move(movement1);
        
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
        hitbox_boxer2.move(movement2);
        
        //BLOCK
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        //DODGE BOXER 1
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)) 
        {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
        {
        hitbox_boxer1.move(boxer1.dodge(sf::Vector2f(-0.5f, 0.f))); 
        
        }   
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))               
        {
        hitbox_boxer1.move(boxer1.dodge(sf::Vector2f(0.5f, 0.f)));  
        
        }   
        }               

                boxer1.handleInput(sf::Keyboard::Key::R, sf::Keyboard::Key::T, sf::Keyboard::Key::Y, sf::Keyboard::Key::U, hitbox_boxer1, hitbox_boxer2,true);
                boxer2.handleInput(sf::Keyboard::Key::F, sf::Keyboard::Key::G, sf::Keyboard::Key::H, sf::Keyboard::Key::J, hitbox_boxer1, hitbox_boxer2,false); 
            
                boxer1.update(boxer2.getSprite().getPosition());
                boxer2.update(boxer1.getSprite().getPosition());
                if (isPaused) 
                {
                    menu.draw(window); 
                }
                else {

                boxer1.update(boxer2.getSprite().getPosition() /*1*/);
                boxer2.update(boxer1.getSprite().getPosition() /*2*/);

                
                handleCollisions();

                ring.draw(window);
                boxer1.draw(window);
                boxer2.draw(window);
                hitbox_boxer1.draw(window);
                hitbox_boxer2.draw(window);
                hitbox_ring.draw(window);
                
                

                break;
            }
        }
    
        window.display();
        
    }
}

void Game::draw() {
    window.clear();
    window.draw(backgroundSprite);

    if (selectedMapIndex == 0) {
        window.draw(ringSprite_);  
    } else if (selectedMapIndex == 1) {
        window.draw(streetSprite_); 
    }

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
    
    sf::FloatRect boxer1BoundSprite = boxer1.getSprite().getGlobalBounds();
    sf::FloatRect boxer2BoundSprite = boxer2.getSprite().getGlobalBounds();
    sf::FloatRect ringBoundSprite = ring.getBounds();

    sf::FloatRect boxer1Bounds = hitbox_boxer1.getShape().getGlobalBounds();
    sf::FloatRect boxer2Bounds = hitbox_boxer2.getShape().getGlobalBounds();
    
    // Colisiones del ring con sprites
    if (boxer1BoundSprite.left < ringBoundSprite.left) {
        boxer1.move({ringBoundSprite.left - boxer1BoundSprite.left, 0});
        hitbox_boxer1.move({ringBoundSprite.left - boxer1BoundSprite.left, 0});
    }
    if (boxer1BoundSprite.left + boxer1BoundSprite.width > ringBoundSprite.left + ringBoundSprite.width) {
        boxer1.move({ringBoundSprite.left + ringBoundSprite.width - (boxer1BoundSprite.left + boxer1BoundSprite.width), 0});
        hitbox_boxer1.move({ringBoundSprite.left + ringBoundSprite.width - (boxer1BoundSprite.left + boxer1BoundSprite.width), 0});
    }
    if (boxer1BoundSprite.top < ringBoundSprite.top) {
        boxer1.move({0, ringBoundSprite.top - boxer1BoundSprite.top});
        hitbox_boxer1.move({0, ringBoundSprite.top - boxer1BoundSprite.top});
    }
    if (boxer1BoundSprite.top + boxer1BoundSprite.height > ringBoundSprite.top + ringBoundSprite.height) {
        boxer1.move({0, ringBoundSprite.top + ringBoundSprite.height - (boxer1BoundSprite.top + boxer1BoundSprite.height)});
        hitbox_boxer1.move({0, ringBoundSprite.top + ringBoundSprite.height - (boxer1BoundSprite.top + boxer1BoundSprite.height)});
    }

    if (boxer2BoundSprite.left < ringBoundSprite.left) {
        boxer2.move({ringBoundSprite.left - boxer2BoundSprite.left, 0});
        hitbox_boxer2.move({ringBoundSprite.left - boxer2BoundSprite.left, 0});
    }
    if (boxer2BoundSprite.left + boxer2BoundSprite.width > ringBoundSprite.left + ringBoundSprite.width) {
        boxer2.move({ringBoundSprite.left + ringBoundSprite.width - (boxer2BoundSprite.left + boxer2BoundSprite.width), 0});
        hitbox_boxer2.move({ringBoundSprite.left + ringBoundSprite.width - (boxer2BoundSprite.left + boxer2BoundSprite.width), 0});
    }
    if (boxer2BoundSprite.top < ringBoundSprite.top) {
        boxer2.move({0, ringBoundSprite.top - boxer2BoundSprite.top});
        hitbox_boxer2.move({0, ringBoundSprite.top - boxer2BoundSprite.top});
    }
    if (boxer2BoundSprite.top + boxer2BoundSprite.height > ringBoundSprite.top + ringBoundSprite.height) {
        boxer2.move({0, ringBoundSprite.top + ringBoundSprite.height - (boxer2BoundSprite.top + boxer2BoundSprite.height)});
        hitbox_boxer2.move({0, ringBoundSprite.top + ringBoundSprite.height - (boxer2BoundSprite.top + boxer2BoundSprite.height)});
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
            } 
            else 
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
        hitbox_boxer1.move(moveDirection);
        hitbox_boxer2.move(-moveDirection);
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


void Game::setBackground(BackgroundType backgroundType) {
    currentBackground = backgroundType;
    
    if (backgroundType == RING) {
        backgroundSprite.setTexture(ringTexture_);
    } else if (backgroundType == STREET) {
        backgroundSprite.setTexture(streetTexture_);
    }
}


void Game::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) 
    {
        if (currentState == GameState::MENU) 
        {
            menu.handleInput(event, window);
        }

    
    }
}

void Game::update() {
    if (currentState == GameState::MENU) 
        {
            menu.update();
        }

    if(isBotActive)
        {
        //moveBot() ? 
        }
    if (!isGameOver) 
{
    if (boxer1.get_hearts() <= 0 || boxer2.get_hearts() <= 0) 
    {
        std::cout << "!!isgameover" << std::endl;
        
        isGameOver = true;  
        currentState = MENU;

        window.clear();
        window.draw(gameOverText);
        window.display();

        sf::sleep(sf::seconds(2)); 

        while (window.isOpen()) 
        {
            sf::Event event;
            while (window.pollEvent(event)) 
            {
                
                if (event.type == sf::Event::Closed) 
                {
                    window.close();
                }
            }
        }
    }
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

bool playWithBot = false;

void Game::setBotActive(bool active) {
    isBotActive = active;
}