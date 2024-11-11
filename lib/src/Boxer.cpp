#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Boxer.hpp"
#include "Collision.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>


// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath, sf::Vector2f spawn)
    : name(name), stamina(max_stamina),max_stamina(100), lucky_in_punch(10), defense(10), speed(10),hearts(10), attacking(false), dodgeSpeed(5.0f),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) {
    loadTexture("idle", initialTexturePath);  // Cargar la imagen inicial
    boxerSprite_.setScale(0.6f, 0.6f);
    boxerSprite_.setTexture(animations_["idle"]);
    boxerSprite_.setOrigin(339/2,336/2);    
    boxerSprite_.setPosition(spawn.x,spawn.y); 
    
    staminaBar.setSize(sf::Vector2f(100.0f, 20.0f)); 
    staminaBar.setFillColor(sf::Color::Green);        
    staminaBar.setOutlineColor(sf::Color::Black);    
    staminaBar.setOutlineThickness(2.0f);
    loadHeartTexture();
    
      }

void Boxer::loadTexture(const std::string& animationName, const std::string& texturePath) 
{
    sf::Texture texture;
    if (!texture.loadFromFile(texturePath)) 
    {
        std::cerr << "!!Error loading texture " << texturePath << std::endl;
    } 
    else 
    {
        animations_[animationName] = texture;
    }
    
}

void Boxer::loadHeartTexture() 
{
    if (!heartTexture.loadFromFile("../../assets/images/hearts.png")) 
    {
        std::cerr << "!!Error loading animation" << std::endl;
    }
    heartSprite.setTexture(heartTexture);
    
    // Ajustar la posición
    heartSprite.setPosition(10, 10); // Ajusta la posición como desees

    // Ajustar el tamaño (escalado)
    float scaleX = 0.25f; 
    float scaleY = 0.25f; 
    heartSprite.setScale(scaleX, scaleY);
}

void Boxer::loadAnimation(const std::string &animationName, const std::string &texturePath) 
{
    sf::Texture animationTexture;
    if (!animationTexture.loadFromFile(texturePath)) 
    {
        std::cerr << "!!Error loading animation " << texturePath << std::endl;
    }
    animations_[animationName] = animationTexture; // Guardar la textura en el mapa
}

//junte entre loadanumation y loadtexture? 

//change boxer animations
void Boxer::setAnimation(const std::string& animationName) 
{
    if (animations_.find(animationName) != animations_.end()) 
    {
        boxerSprite_.setTexture(animations_[animationName]);
    } 
    else 
    {
        std::cerr << "!!animation not found " << animationName << std::endl;
    }
}

// action methods
void Boxer::jab_right(Collision& hitbox1, Collision& hitbox2,bool isBoxer1) 
{
    if (stamina < 10) {
        std::cout << name << "Nesesitas recuperar energia" << std::endl;
        return; 
    }
    
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        //take_damage(1);
        
        if(isBoxer1)
        {
            loadAnimation("jab_right", "../../assets/images/right_red.png");
        }
        else
        {
            loadAnimation("jab_right", "../../assets/images/right_blue.png");
        }

        setAnimation("jab_right");

        
        hitbox1.expand(sf::Vector2f(20.f, 20.f)); 
        hitbox2.expand(sf::Vector2f(20.f, 20.f)); 
       
    }

    else {
        hitbox1.reset();
        hitbox2.reset();
        state = BoxerState::IDLE;
    }
}


void Boxer::jab_left(Collision& hitbox1, Collision& hitbox2,bool isBoxer1) 
{
    if (stamina < 10)
    {
        std::cout << name << " Necesitas recuperar energía" << std::endl;
        return;
    }

    if (state == BoxerState::IDLE) {
        state = BoxerState::ATTACKING;
        punchClock.restart();
        reduce_stamina(10);
        if(isBoxer1)
        {
            loadAnimation("jab_left", "../../assets/images/left_red.png");
        }
        else
        {
            loadAnimation("jab_left", "../../assets/images/left_blue.png");
        }
        setAnimation("jab_left");

        hitbox1.expand(sf::Vector2f(20.f, 20.f)); 
        hitbox2.expand(sf::Vector2f(20.f, 20.f)); 
    }

    else {
        hitbox1.reset();
        hitbox2.reset();
        state = BoxerState::IDLE;
    }
}

/*void Boxer::setOpponent(Boxer* opponent) {
    this->opponent = opponent;
}*/



void Boxer::hook() 
{
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("hook", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/hook.png");

        setAnimation("hook");  
        //FALTA AJUSTAR STAMINA
    }

    if (stamina >= 8) {  
        state = BoxerState::ATTACKING;
        reduce_stamina(10);  
    }
}

void Boxer::uppercut() 
{
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("uppercut", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/uppercut.png");

        setAnimation("uppercut"); 
    }
}

void Boxer::block() 
{

    if (state == BoxerState::IDLE) 
    { 
        if(stamina < 20)
        {
            std::cout << name << " no se puede bloquear recupera energia" << std::endl;

            return;
        }
        state = BoxerState::BLOCKING;
        reduce_stamina(20);  
        blockClock.restart();
        loadAnimation("block", "../../assets/images/block.png");

        setAnimation("block"); 

        std::cout << name << " está bloqueando." << std::endl;

    } 
}
void Boxer::unblock() 
{
    if (state == BoxerState::BLOCKING)
    {
        setState(BoxerState::IDLE);
        loadAnimation("boxer", "../../assets/images/boxer.png"); 
        setAnimation("boxer");
    }
}

void Boxer::dodge(sf::Vector2f direction) 
{
    
    state = BoxerState::DODGING;
    float dodgeDistance = 01.f; 

    sf::Vector2f dodgeMovement = direction * dodgeDistance;
    state = BoxerState::DODGING;

    move(direction * dodgeSpeed);
    dodgeClock.restart().asSeconds();
    reduce_stamina(40);
    std::cout << name << "se esquivo" << std::endl;
        
    
 }   

//methods damage
void Boxer::take_damage(int amount) 
{
    if (state == BoxerState::BLOCKING) 
    {
        std::cout << name << " bloqueó el golpe y no recibió daño." << std::endl;
        return;
    }

     hearts -= amount; 
    if (hearts < 0) 
    {
        hearts = 0; 
    
    }
}

void Boxer::receivePunch() {
    if (hearts > 0) {
        hearts--;  
        state = BoxerState::TAKING_DAMAGE;
        std::cout << "¡Golpe recibido! Corazones restantes x: " << hearts << std::endl;
    } 
    else if(hearts == 0)
        {
        std::cout << "El boxeador ya no tiene corazones, ganaste" << std::endl;
    }
}


void Boxer::reduce_stamina(float amount) 
    {
    stamina -= amount;
    if (stamina < 0) stamina = 0;
}
//
//stamina
void Boxer::recover_stamina(float amount) {
    stamina += amount;
    if (stamina > max_stamina) stamina = max_stamina;
}

void Boxer::updateStaminaBar() {
    float staminaPercentage = stamina / max_stamina; 
    staminaBar.setSize(sf::Vector2f(100.0f * staminaPercentage, 20.0f));
}


void Boxer::enqueue_action(Action action) 
{
    action_queue.push(action);
}

void Boxer::updatefps(float deltaTime) {
    position.x += speed * deltaTime;
}


void Boxer::update(const sf::Vector2f& opponentPosition ) 
{
    if (state == BoxerState::ATTACKING && punchClock.getElapsedTime() > punchDuration) 
    {
        state = BoxerState::IDLE;
        setAnimation("idle");
    }
     
    if (state == BoxerState::IDLE) 
    {
    recover_stamina(0.05f);  
    }

    if (state == BoxerState::DODGING && dodgeClock.getElapsedTime().asSeconds() > 0.5f) 
    {
    state = BoxerState::IDLE;
    }

    if (state == BoxerState::BLOCKING && blockClock.getElapsedTime().asSeconds() > 2.0f) {
        unblock(); 
    }

    //boxer rotation 
    sf::Vector2f direction = opponentPosition - boxerSprite_.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / M_PI;
    boxerSprite_.setRotation(angle + 278);
    
    
}

void Boxer::increase_ko_probability(int amount) 
{
    ko_probability += amount;
}

bool Boxer::attempt_knockout() // only first punch/hit
{
    int chance = std::rand() % 100;
    if (chance < ko_probability) 
    {
        knocked_out = true;
        return true;  // K.O. successful
    }
    return false;  // not K.O. change code style
}

bool Boxer::is_knocked_out() const 
{
    return knocked_out;
}

void Boxer::check_for_technical_ko() 
{
    if (stamina <= 0) 
    {
        knocked_out = true;  
        std::cout <<"k.o tecnico" << std::endl;
    }
}


const std::string& Boxer::get_name() const 
    {
        return name;
    }

float Boxer::get_stamina() const 
{
    return stamina;
}

float Boxer::get_max_stamina() const
{
    return max_stamina;
}

int Boxer::get_lucky_in_punch() const 
{
    return lucky_in_punch;
}

int Boxer::get_defense() const 
{
    return defense;
}

int Boxer::get_speed() const 
{
    return speed;
}

int Boxer::get_hearts() const 
{
    return hearts;
}

BoxerState Boxer::getState() const
{
    return state; 
}

void Boxer::setState(BoxerState newState) {
    state = newState; 
}

void Boxer::move(sf::Vector2f direction) {
    boxerSprite_.move(direction);
}


void Boxer::draw(sf::RenderWindow& window) {
    
    window.draw(boxerSprite_);
    //draw hearts

    float heartWidth = heartSprite.getGlobalBounds().width;
    float spacing = heartWidth + 0.2;  // spacing hearts
    int heartsToDraw = hearts; // number hearts 
    
    // Draw hearts acttually
    float startX = isleft ? 50 : window.getSize().x - (spacing * 10) - 50;
    float startY = 20; 

    for (int i = 0; i < get_hearts(); ++i) {
        heartSprite.setPosition(startX + i * spacing, startY);  // Usar 'position' aquí
        window.draw(heartSprite);
    }

    // draw hotbar stamina
    staminaBar.setSize(sf::Vector2f((stamina / max_stamina) * 100, 10)); // size
    staminaBar.setPosition(getBounds().left, getBounds().top - 20);  // position the stamina 
    window.draw(staminaBar);
}

sf::FloatRect Boxer::getBounds() const {
    return boxerSprite_.getGlobalBounds();
}

void Boxer::setPosition(float x, float y) {
    head.setPosition(x, y);
}

void Boxer::setColor(sf::Color color) {
    head.setFillColor(color);
}

const sf::Sprite& Boxer::getSprite() const {
    return boxerSprite_;
}

void Boxer::handleInput(sf::Keyboard::Key attack1, sf::Keyboard::Key attack2, 
                        sf::Keyboard::Key attack3, sf::Keyboard::Key attack4,
                        Collision& hitbox1, Collision& hitbox2,bool isBoxer1) 
{
    if (sf::Keyboard::isKeyPressed(attack1)) {
        jab_right(hitbox1, hitbox2, isBoxer1); 
        setState(BoxerState::ATTACKING);
    }
    
    if (sf::Keyboard::isKeyPressed(attack3)) {
        jab_left(hitbox1, hitbox2, isBoxer1); 
        setState(BoxerState::ATTACKING);
    }
}



void Collision::expand(const sf::Vector2f& expansionSize) 
{
    rectangle.setSize(originalSize + expansionSize);
    rectangle.setOrigin((originalSize + expansionSize) / 2.f);  
}

void Collision::reset() 
{
    rectangle.setSize(originalSize);
    rectangle.setOrigin(originalSize / 2.f);  
}

sf::Vector2f Boxer::getPosition()
{
    return boxerSprite_.getPosition();
}

