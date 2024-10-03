#include "boxer.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>

// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath) 
    : name(name), stamina(100), lucky_in_punch(10), defense(10), speed(10),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) {
    loadTexture("idle", initialTexturePath);  // Cargar la imagen inicial
    boxerSprite_.setScale(0.5f, 0.5f);
    boxerSprite_.setTexture(animations_["idle"]);
    boxerSprite_.setPosition(300, 300); // Posición inicial
    
      }

Boxer::Boxer(sf::Color color) 
    : name("Default Boxer"), stamina(100), lucky_in_punch(10), defense(10), speed(10), 
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f) {
    head.setRadius(25);
    head.setFillColor(color); 
    head.setPosition(200, 200); // inicial position
}
/////textures animations etc...
//load animation textures

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

void Boxer::loadAnimation(const std::string &animationName, const std::string &texturePath) 
{
    sf::Texture animationTexture;
    if (!animationTexture.loadFromFile(texturePath)) 
    {
        std::cerr << "!!Error loading animation " << texturePath << std::endl;
    }
    animations_[animationName] = animationTexture; // Guardar la textura en el mapa
}

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
void Boxer::jab_right() 
{
    if (state == BoxerState::IDLE) { 
        state = BoxerState::ATTACKING;
        punchClock.restart(); 

        loadAnimation("jab", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/right_jab.png");
        
        setAnimation("jab"); 
    }
}

void Boxer::jab_left()
{
if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("jab_left", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/left_jab.png");

        setAnimation("jab_left");  
    }
}

void Boxer::hook() 
{
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("hook", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/hook.png");

        setAnimation("hook");  
        //FALTA AJUSTAR STAMINA
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
    std::cout << name << " blocking." << std::endl;
    defense += 10;
    state = BoxerState::BLOCKING;
}

void Boxer::dodge() 
{
    std::cout << name << " try to dodge" << std::endl;
    if (rand() % 100 < speed) {
        std::cout << name << " successfully dodged!" << std::endl;
    }   
    else 
    {
        std::cout << name << " failed dodge" << std::endl;
    }
    state = BoxerState::DODGING;
}

void Boxer::take_damage(int amount) 
{
    if (defense > 0) 
    {
        amount -= defense / 2;
        defense = 0;
    }
    
    if (amount > 0) 
    {
        stamina -= amount;
        std::cout << name << " took " << amount << " damage" << std::endl;
    } 
    
    else 
    {
        std::cout << name << " blocked all the damage!" << std::endl;
    }

    check_for_technical_ko();
    state = BoxerState::TAKING_DAMAGE;
}

void Boxer::enqueue_action(Action action) 
{
    action_queue.push(action);
}

void Boxer::update() {

    if (state == BoxerState::ATTACKING && punchClock.getElapsedTime() > punchDuration) {
        state = BoxerState::IDLE; 
    }
}

void Boxer::increase_ko_probability(int amount) 
{
    ko_probability += amount;
}

bool Boxer::attempt_knockout() 
{
    int chance = std::rand() % 100;
    if (chance < ko_probability) 
    {
        knocked_out = true;
        return true;  // K.O. successful
    }
    return false;  // not K.O.
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
    }
}


const std::string& Boxer::get_name() const 
    {
        return name;
    }

int Boxer::get_stamina() const 
{
    return stamina;
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


void Boxer::move(sf::Vector2f direction) {
    boxerSprite_.move(direction);
}

void Boxer::draw(sf::RenderWindow& window) {
    window.draw(boxerSprite_);
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

void Boxer::handleInput(sf::Keyboard::Key attack1, sf::Keyboard::Key attack2, 
                        sf::Keyboard::Key attack3, sf::Keyboard::Key attack4) 
{
    if (sf::Keyboard::isKeyPressed(attack1)) {
        jab_right(); // Acción para el primer ataque
    }
    if (sf::Keyboard::isKeyPressed(attack2)) {
        uppercut(); // Acción para el segundo ataque
    }
    if (sf::Keyboard::isKeyPressed(attack3)) {
        jab_left(); // Acción para el tercer ataque
    }
    if (sf::Keyboard::isKeyPressed(attack4)) {
        hook(); // Acción para el cuarto ataque
    }
}