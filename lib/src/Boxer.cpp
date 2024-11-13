#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Boxer.hpp"
#include "Collision.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>
#include <list.hpp>

// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath, sf::Vector2f spawn)
    : name(name),Health(maxHealth),maxHealth(100), stamina(max_stamina),max_stamina(100), lucky_in_punch(10), defense(10), speed(10), attacking(false), dodgeSpeed(5.0f),
    ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) {
    loadTexture("idle", initialTexturePath);  
    boxerSprite_.setScale(0.6f, 0.6f);
    boxerSprite_.setTexture(animations_["idle"]);
    boxerSprite_.setOrigin(339/2,336/2);    
    boxerSprite_.setPosition(spawn.x,spawn.y); 
    
staminaBar.setSize(sf::Vector2f(200.f, 20.f)); 
staminaBar.setFillColor(sf::Color::Green);
staminaBar.setPosition(50.f, 50.f);  

staminaBarBackground.setSize(sf::Vector2f(200.f, 20.f));
staminaBarBackground.setFillColor(sf::Color(50, 50, 50)); 
staminaBarBackground.setPosition(50.f, 50.f);  

HealthBar.setSize(sf::Vector2f(300.f, 25.f)); 
HealthBar.setFillColor(sf::Color::Red);
HealthBar.setPosition(250.f, 20.f);  

healthBarBackground.setSize(sf::Vector2f(300.f, 25.f));
healthBarBackground.setFillColor(sf::Color(50, 50, 50)); 
healthBarBackground.setPosition(250.f, 20.f);

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

void Boxer::unblock(bool isBoxer1) 
{

    if (state == BoxerState::BLOCKING) 
    {
        setState(BoxerState::IDLE);
        
        if(isBoxer1)
        {
            loadAnimation("boxer", "../../assets/images/boxer.png");
        }
        else
        {
            loadAnimation("boxer", "../../assets/images/boxer2.png");
        }
        setAnimation("boxer");
        std::cout << name << " dejó de bloquear." << std::endl;
    }
}

void Boxer::block(Collision& hitbox1, Collision& hitbox2, bool isBoxer1)
{
    
    if (state != BoxerState::BLOCKING) 
    {
        if (stamina < 20) 
        {
            std::cout << name << " no tiene suficiente energía para bloquear." << std::endl;
            return; 
        }

        setState(BoxerState::BLOCKING);

        if (isBoxer1)
            loadAnimation("block", "../../assets/images/blockred.png");
        else
            loadAnimation("block", "../../assets/images/blockblue.png");

        setAnimation("block");
        blockClock.restart();
        std::cout << name << " está bloqueando." << std::endl;
    }

    
    if (state == BoxerState::BLOCKING) 
    {
        if (blockClock.getElapsedTime().asMilliseconds() > 100) 
        {
            reduce_stamina(1);
            blockClock.restart();

            if (stamina < 0.5) 
            {
                std::cout << name << " se queda sin estamina, deja de bloquear." << std::endl;
                unblock(isBoxer1);
            }
        }
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




sf::Vector2f Boxer::dodge(sf::Vector2f direction) 
{
    
    state = BoxerState::DODGING;
    float dodgeDistance = 5.0f; 

    sf::Vector2f dodgeMovement = direction * dodgeDistance;
    state = BoxerState::DODGING;

    move(direction * dodgeSpeed);
    dodgeClock.restart().asSeconds();
    reduce_stamina(20);
    std::cout << name << "esquivo" << std::endl;
        
    
}   

//methods damage
void Boxer::take_damage(int amount) 
{
    if (state == BoxerState::BLOCKING) 
    {
        std::cout << name << " bloqueó el golpe y no recibió daño." << std::endl;
        return;
    }

    Health -= amount;
    if (Health < 0) Health = 0;

}

void Boxer::receivePunch(int amount) {
    
    if (state == BoxerState::BLOCKING) {
        std::cout << name << " bloqueó el golpe y no recibió daño." << std::endl;
        return;
    }
    
    if (damageCooldownClock.getElapsedTime() < damageCooldown) {
        return; 
    }
    damageCooldownClock.restart();
    
    Health -= amount;
    
    if (Health < 0) {
        Health = 0;
    }
    std::cout << "¡Golpe recibido! Vida restante: " << Health << "/" << maxHealth << std::endl;

    
    if (Health > 0) {
        state = BoxerState::TAKING_DAMAGE;
    } 
    
    else {
        std::cout << "El boxeador ha sido derrotado, K.O." << std::endl;
        state = BoxerState::K_O;
        loadAnimation("ko", "../../assets/images/ko.png");
        setAnimation("ko");
    }
    float healthRatio = Health / maxHealth;
    HealthBar.setSize(sf::Vector2f(300.f * healthRatio, 25.f)); 
}

void Boxer::updateHealthBar(){
    float healthRatio = Health / maxHealth;
    HealthBar.setSize(sf::Vector2f(300.f * healthRatio, 25.f));
}

void Boxer::reduce_stamina(float amount) 
    {
    stamina -= amount;
    if (stamina < 0) stamina = 0;
    
    float staminaRatio = stamina / max_stamina;
    staminaBar.setSize(sf::Vector2f(200.f * staminaRatio, 20.f));
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

int Boxer::get_Health() const 
{
    return Health;
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
    window.draw(staminaBarBackground);
    window.draw(staminaBar);

    window.draw(healthBarBackground);
    window.draw(HealthBar);
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
                        sf::Keyboard::Key keyblock, Collision& hitbox1,
                        Collision& hitbox2, bool isBoxer1) 
{
    if (sf::Keyboard::isKeyPressed(keyblock)) {
        block(hitbox1, hitbox2, isBoxer1);
    } else {
        // Si no se presiona el botón de bloqueo, dejar de bloquear
        if (state == BoxerState::BLOCKING) {
            unblock(isBoxer1);
        }
    }

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

