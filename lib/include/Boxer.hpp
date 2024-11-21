#pragma once
#include <string>
#include <queue>
#include <functional>
#include "Collision.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include "BehaviorTree.hpp"

using Action = std::function<void()>;

enum class BoxerState 
    {
    IDLE,
    ATTACKING,
    BLOCKING,
    DODGING,
    TAKING_DAMAGE,
    K_O,
    INVINCIBLE
    };

class Boxer 
    {
public:
    
    Boxer(const std::string& name, const std::string& initialTexturePath, sf::Vector2f spawn);
    void loadTexture(const std::string& animationName, const std::string& texturePath);
    void loadAnimation(const std::string &animationName, const std::string &texturePath);
    void move(sf::Vector2f direction);
    void reset();
    sf::Vector2f getPosition();
    


    void handleInput(sf::Keyboard::Key attack1, sf::Keyboard::Key attack3, Collision& hitbox1, Collision& hitbox2, bool isBoxer1, sf::Keyboard::Key keyblock, sf::Keyboard::Key dodge_move);

    Boxer() : state(BoxerState::IDLE), punchDuration(sf::seconds(0.2f)) {}
    const sf::Sprite&  getSprite() const;

    // draw the boxer

    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);

    void setColor(sf::Color color); // ?
    void setAnimation(const std::string& animationName); //change animation
    sf::RectangleShape staminaBar;
    void loadHeartTexture();
    void drawHearts(sf::RenderWindow& window, int heartsCount, bool isLeft);

    void jab_right(Collision& hitbox1, Collision& hitbox2,bool isBoxer1);
    void jab_left(Collision& hitbox1, Collision& hitbox2,bool isBoxer1);

    void block(Collision& hitbox1, Collision& hitbox2, bool isBoxer1);
    void unblock(bool); 
    
    
    sf::Vector2f dodge(sf::Vector2f direction);

    
    bool isinrange(const Boxer& opponent, float range) const;
    
    void enqueue_action(Action action);
    void update(const sf::Vector2f& opponentPosition);
    void updatefps(float deltatime);
    // methods K.O.
    void increase_ko_probability(int amount);
    bool attempt_knockout();
    bool is_knocked_out() const;
    void check_for_technical_ko();

    // Stamina
    void updateStaminaBar(); 
    void reduce_stamina(float amount);        
    void recover_stamina(float amount);      
    float get_stamina() const;                
    float get_max_stamina() const;   

    void take_damage(int amount);
    void receivePunch(int amount);

    const std::string& get_name() const;
    int get_lucky_in_punch() const;
    int get_defense() const;
    int get_speed() const;
    int get_hearts() const;

    BoxerState getState() const; 
    void setState(BoxerState state);
    sf::Vector2f vector;
    //BehaviorTree
    /*NodeStatus jabRightAction(Collision& hitbox1, Collision& hitbox2, float distance);
    void initBehaviorTree(Collision& hitbox1, Collision& hitbox2, float distance );
    void Ian_Right_jab(Collision& hitbox1, Collision& hitbox2);
    void Ian_Left_jab();*/

    
    private:


    std::string name;
    
    Boxer* opponent = nullptr; 

    float max_stamina; 
    float stamina;               
    int lucky_in_punch;
    int defense;    
    int speed;
    int ko_probability; 
    bool knocked_out;   
    float dodgeSpeed;
    
    int hearts;  
    bool attacking;   
    bool isleft;
    
    sf::Clock blockClock;
    sf::Clock damageCooldownClock;
    sf::Time damageCooldown = sf::milliseconds(1000);
    //BT
    //std::shared_ptr<BehaviorNode> behaviorTreeRoot;
    
    
    sf::Sprite boxerSprite_;
    std::map<std::string, sf::Texture> animations_;
    sf::CircleShape head; //?

    sf::Clock dodgeClock; 
    
    sf::Vector2f position;
    BoxerState state;  // manage state
    
    sf::Clock punchClock;
    sf::Time punchDuration;
    std::queue<Action> action_queue;  // action queue
    float time_accumulated;           // accumulated time
    float action_interval;
    sf::Texture heartTexture;  // heart textur
    sf::Sprite heartSprite; 
};
