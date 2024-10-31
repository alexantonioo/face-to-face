#include "Game.hpp"
#include "Boxer.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>


// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath) 
    : name(name), stamina(max_stamina),max_stamina(100), lucky_in_punch(10), defense(10), speed(10),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) {
    loadTexture("idle", initialTexturePath);  // Cargar la imagen inicial
    boxerSprite_.setScale(0.3f, 0.3f);
    boxerSprite_.setTexture(animations_["idle"]);
    boxerSprite_.setPosition(300, 300); 
    staminaBar.setSize(sf::Vector2f(100.0f, 20.0f)); 
    staminaBar.setFillColor(sf::Color::Green);        
    staminaBar.setOutlineColor(sf::Color::Black);    
    staminaBar.setOutlineThickness(2.0f);
    
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
void Boxer::jab_right() 
{
    if (stamina < 10) {
        return; 
    }
    
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        
        loadAnimation("jab_right", "/mnt/c/Users/marus/OneDrive/Documents/GitHub/face-to-face/assets/images/right_jab.png");

        setAnimation("jab_right");
    }
}


void Boxer::jab_left()
{
    if (stamina < 10) 
        {
        return;  
    }
   
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        
        loadAnimation("jab_left", "/mnt/c/Users/marus/OneDrive/Documents/GitHub/face-to-face/assets/images/left_jab.png");
        setAnimation("jab_left");  
    }
}

void Boxer::hook() 
{
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("hook", "/mnt/c/Users/marus/OneDrive/Documents/GitHub/face-to-face/assets/images/hook.png");

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

        loadAnimation("uppercut", "/mnt/c/Users/marus/OneDrive/Documents/GitHub/face-to-face/assets/images/uppercut.png");

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



void Boxer::reduce_stamina(float amount) 
    {
    stamina -= amount;
    if (stamina < 0) stamina = 0;
}

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

void Boxer::update(const sf::Vector2f& opponentPosition) 
{
    if (state == BoxerState::ATTACKING && punchClock.getElapsedTime() > punchDuration) 
    {
        state = BoxerState::IDLE;
        setAnimation("idle");
    }
     
        if (state == BoxerState::IDLE) {
        recover_stamina(0.05f);  // recovery stamina 
        }

    //boxer rotation
    sf::Vector2f direction = opponentPosition - boxerSprite_.getPosition();
    float angle = std::atan2(direction.y, direction.x) * 180 / 3.14159265;

    boxerSprite_.setRotation(angle + 292); 
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


void Boxer::move(sf::Vector2f direction) {
    boxerSprite_.move(direction);
}

void Boxer::draw(sf::RenderWindow& window) {
    window.draw(boxerSprite_);

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
                        sf::Keyboard::Key attack3, sf::Keyboard::Key attack4) 
{
    if (sf::Keyboard::isKeyPressed(attack1)) {
        jab_right(); // Acción para el primer ataque
    }
    
    if (sf::Keyboard::isKeyPressed(attack3)) {
        jab_left(); // Acción para el tercer ataque
    }
}