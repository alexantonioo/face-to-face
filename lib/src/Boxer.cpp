#include <SFML/Graphics.hpp>
#include "Game.hpp"
#include "Boxer.hpp"
#include "Collision.hpp"
#include "Path.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>
#include <cmath>
#include "BehaviorTree.hpp" 

// Constructor
Boxer::Boxer(const std::string& name, const std::string& initialTexturePath, sf::Vector2f spawn)
    : name(name), stamina(max_stamina),max_stamina(100), lucky_in_punch(10), defense(10), speed(10),hearts(10), attacking(false), dodgeSpeed(5.0f),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f), punchDuration(sf::seconds(0.5f)) 
    {
        loadTexture("idle", initialTexturePath);  
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
    if (!heartTexture.loadFromFile(Path::HEART_TEXTURE_PATH)) 
    {
        std::cerr << "!!Error loading animation" << std::endl;
    }
    heartSprite.setTexture(heartTexture);
    
    heartSprite.setPosition(10, 10); // Ajusta la posición como desees

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
    if (damageCooldownClock.getElapsedTime() < damageCooldown) {
        std::cout << name << " aún está en cooldown de golpe\n";
        return; 
    }

    if (stamina < 10) {
        std::cout << name << "Nesesitas recuperar energia" << std::endl;
        return; 
    }
    
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        damageCooldownClock.restart();
        
        if(isBoxer1)
        {
            loadAnimation("jab_right", Path::RIGHTRED_TEXTURE_PATH);
        }
        else
        {
            loadAnimation("jab_right", Path::RIGHTBLUE_TEXTURE_PATH);
        }

        setAnimation("jab_right");

        damageCooldownClock.restart();
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
    if (damageCooldownClock.getElapsedTime() < damageCooldown) {
        std::cout << name << " aún está en cooldown de golpe\n";
        return; 
    }

    if (stamina < 10)
    {
        std::cout << name << " Necesitas recuperar energía" << std::endl;
        return;
    }

    if (state == BoxerState::IDLE) {
        state = BoxerState::ATTACKING;
        punchClock.restart();
        reduce_stamina(10);
        damageCooldownClock.restart();

        if(isBoxer1)
        {
            loadAnimation("jab_left", Path::LEFTRED_TEXTURE_PATH);
        }
        else
        {
            loadAnimation("jab_left", Path::LEFTBLUE_TEXTURE_PATH);
        }
        setAnimation("jab_left");

        damageCooldownClock.restart();
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
            loadAnimation("idle", Path::IDLERED_TEXTURE_PATH);
        }
        else
        {
            loadAnimation("idle", Path::IDLEBLUE_TEXTURE_PATH);
        }
        setAnimation("idle");
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

            
        if (isBoxer1){
            loadAnimation("block", Path::BLOCKRED_TEXTURE_PATH);
        }
            
        else{
            loadAnimation("block", Path::BLOCKBLUE_TEXTURE_PATH);
        }

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

sf::Vector2f Boxer::dodge(sf::Vector2f direction)
{
    
    state = BoxerState::DODGING;
    float dodgeDistance = 100.0f; 
    float dodgeSpeed = 5.0f;  

    sf::Vector2f dodgeMovement = direction * dodgeDistance;
    state = BoxerState::DODGING;

    move(direction * dodgeSpeed);
    dodgeClock.restart().asSeconds();
    reduce_stamina(20);
    std::cout << name << "esquivo" << std::endl;
        
    return sf::Vector2f(direction * dodgeSpeed);
 }   

//methods damage
void Boxer::take_damage(int amount) 
{
    if (damageCooldownClock.getElapsedTime() >= damageCooldown) {
        if (hearts > 0) {
            hearts--; 
            std::cout << name << " pierde un corazón. Corazones restantes: " << hearts << std::endl; 

    
    if (hearts <= 0) {
        std::cout << name << " ha sido derrotado.\n";
        state = BoxerState::TAKING_DAMAGE;
            }
        }
    } 
}

void Boxer::receivePunch(int amount) {
    
    if (state == BoxerState::INVINCIBLE) {
        std::cout << name << " está invencible, no recibe daño.\n";
        return;
    }

    if (hearts > 0) {
        hearts--;  
        state = BoxerState::TAKING_DAMAGE;
        std::cout << "¡Golpe recibido! Corazones restantes x: " << hearts << std::endl;
    } 

    state = BoxerState::INVINCIBLE;
    damageCooldownClock.restart(); 

    if(hearts == 0)
        {
        std::cout << "El boxeador ya no tiene corazones, ganaste" << std::endl;
        loadAnimation("ko", Path::KO_TEXTURE_PATH);
        setAnimation("ko");
        return;
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
    staminaBar.setSize(sf::Vector2f(200.0f * staminaPercentage, 20.0f));
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
    if (state == BoxerState::INVINCIBLE && damageCooldownClock.getElapsedTime().asSeconds() > 1.0f) {
        state = BoxerState::IDLE;
        std::cout << name << " ya no es invencible.\n";
    }

    if (behaviorTreeRoot) {
        behaviorTreeRoot->tick();  
    }
    
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
        heartSprite.setPosition(startX + i * spacing, startY);  
        window.draw(heartSprite);
    }

    // draw hotbar stamina
    staminaBar.setSize(sf::Vector2f((stamina / max_stamina) * 100, 10)); 
    staminaBar.setPosition(getBounds().left, getBounds().top - 20); 
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

void Boxer::handleInput(sf::Keyboard::Key attack1,sf::Keyboard::Key attack3,
                        Collision& hitbox1,Collision& hitbox2,bool isBoxer1,
                        sf::Keyboard::Key keyblock,sf::Keyboard::Key dodgemove) 
{
    if (sf::Keyboard::isKeyPressed(keyblock)) {
        block(hitbox1, hitbox2, isBoxer1);
    } 
    else {
        
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
    if (sf::Keyboard::isKeyPressed(dodgemove)) {
        
        if (get_stamina() > 20 && dodgeClock.getElapsedTime().asSeconds() >= 1.0f) {
            
            sf::Vector2f dodgeDirection = isBoxer1 ? sf::Vector2f(-1.0f, 0.0f) : sf::Vector2f(1.0f, 0.0f);
            dodge(dodgeDirection); 
        } 

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

void Boxer::Ian_Right_jab(Collision& hitbox1, Collision& hitbox2)
{
   
    
    if (state == BoxerState::IDLE) {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  
        reduce_stamina(10);
        
        

        
        loadAnimation("jab_right", "../../assets/images/right_blue.png");
        

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




NodeStatus Boxer::jabRightAction(Collision& hitbox1, Collision& hitbox2, float distance) {
    float delta = sqrt(pow(hitbox1.getPosition().x - hitbox2.getPosition().x, 2) + pow(hitbox1.getPosition().y - hitbox2.getPosition().y, 2));

    std::cout << delta << " metros" << std::endl;
    
    

    if (stamina >= 10 && delta < 37) {
        Ian_Right_jab(hitbox1, hitbox2);
        return NodeStatus::Success;
    } 
    
    if(punchDuration < sf::seconds(0.5)){
            punchClock.restart();
            reduce_stamina(10);
            return NodeStatus::Failure;
        }

    else {
        return NodeStatus::Failure;
    }
}


void Boxer::initBehaviorTree(Collision& hitbox1, Collision& hitbox2, float distance) 
{
    
    auto jabRightNode = std::make_shared<ActionNode>([this, &hitbox1, &hitbox2, &distance]() { return this->jabRightAction( hitbox1, hitbox2, distance); });
    
    //auto dodgeNode = std::make_shared<ActionNode>([this]() { return this->dodgeAction(); });

    auto rootSequence = std::make_shared<SequenceNode>();
    rootSequence->addChild(jabRightNode);
    
    //rootSequence->addChild(dodgeNode);
    
    behaviorTreeRoot = rootSequence;  
}

