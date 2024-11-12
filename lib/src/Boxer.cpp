#include "Game.hpp"
#include "Boxer.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>
#include <graph.hpp>

// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath, sf::Vector2f spawn)
    : name(name), stamina(max_stamina),max_stamina(100), lucky_in_punch(10), defense(10), speed(10),hearts(10), attacking(false), dodgeSpeed(5.0f),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) {
    loadTexture("idle", initialTexturePath);  // Cargar la imagen inicial
    boxerSprite_.setScale(sf::Vector2f(0.5, 0.5));
    boxerSprite_.setTexture(animations_["idle"]);
    boxerSprite_.setOrigin((341/2)-40,336/2);    
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
void Boxer::jab_right() 
{
    if (stamina < 10) {
        std::cout << name << "Nesesitas recuperar energia" << std::endl;
        return; 
    }
    
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        
        loadAnimation("jab_right", "../../assets/images/right_jab.png");

        setAnimation("jab_right");
        
       
    }
}


void Boxer::jab_left()
{
    if (stamina < 10) 
        {
        std::cout << name << "Nesesitas recuperar energia" << std::endl;
        return;  
    }
   
    if (state == BoxerState::IDLE) {  
      
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        loadAnimation("jab_left", "../../assets/images/left_jab.png");
        setAnimation("jab_left");

       
    }
}

void Boxer::hook() 
{
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("hook", "../../assets/images/hook.png");

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

        loadAnimation("uppercut", "../../assets/images/uppercut.png");

        setAnimation("uppercut");  
    }
}

void Boxer::block() 
{
    std::cout << name << " blocking." << std::endl;
    defense += 10;
    state = BoxerState::BLOCKING;
}

void Boxer::dodge(sf::Vector2f direction) 
    {
        
    float dodgeDistance = 01.f; 

    sf::Vector2f dodgeMovement = direction * dodgeDistance;
    state = BoxerState::DODGING;

    move(direction * dodgeSpeed); // dodgeClock.restart().asSeconds()
    dodgeClock.restart();
    reduce_stamina(40);
        if(state == BoxerState::DODGING)
        {
    std::cout << name << " intenta esquivar" << std::endl;
    }
}

//methods damage
void Boxer::take_damage(int amount) 
{
     hearts -= amount; 
    if (hearts < 0) 
    {
        hearts = 0; 
    
    }
    
    else{
    check_for_technical_ko();
    state = BoxerState::TAKING_DAMAGE;
}
    
    check_for_technical_ko();
    state = BoxerState::TAKING_DAMAGE;
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

bool Boxer::isAttacking() const {
    return state == BoxerState::ATTACKING;  
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

void Boxer::update(const sf::Vector2f& opponentPosition  /*, int p*/) 
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

    //boxer rotation (viejo)
    sf::Vector2f direction = opponentPosition - boxerSprite_.getPosition();
    float angle = std::atan2(/*opponentPosition.y, opponentPosition.x*/direction.y, direction.x) * 180 / M_PI;
    boxerSprite_.setRotation(angle + 300);
    
    //if(p == 1)
    //{
      //  boxerSprite_.setRotation(0 /*angle + 300*/); 
    //}
     
    //if(p == 2)
    //{
        //boxerSprite_.setOrigin(193,138.5);
     //   boxerSprite_.setRotation(180/*angle + 300*/);
    //}
    

    
    
    //prototipo fallido de mirardas
    
    
    /*sf::Vector2f direction = opponentPosition - boxerSprite_.getPosition();
    
    float mod = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (mod != 0) {
        sf::Vector2f UnitDirection = direction / mod;

        if (UnitDirection.x < 0) {
            boxerSprite_.setScale(-0.5f, 0.5f); 
        } else {
            boxerSprite_.setScale(0.5f, 0.5f);  
        }
    }*/
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
                        sf::Keyboard::Key attack3, sf::Keyboard::Key attack4) 
{
    if (sf::Keyboard::isKeyPressed(attack1)) {
        jab_right(); // Acción para el primer ataque
        setState(BoxerState::ATTACKING);
    }
    
    if (sf::Keyboard::isKeyPressed(attack3)) {
        jab_left(); // Acción para el tercer ataque
        setState(BoxerState::ATTACKING);
}
}