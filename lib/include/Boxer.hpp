#pragma once
#include <string>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

    
using Action = std::function<void()>;

    // boxer possible states 
enum class BoxerState 
    {
    IDLE,
    ATTACKING,
    BLOCKING,
    DODGING,
    TAKING_DAMAGE
    };

class Boxer 
    {
public:
    Boxer(const std::string& name);  // Constructor name
    Boxer(sf::Color color);           // Constructor color
    Boxer(const std::string& name, sf::Color color); // Constructor color/name
    Boxer(const std::string& name, const std::string& initialTexturePath);
    void loadTexture(const std::string& animationName, const std::string& texturePath);
    void loadAnimation(const std::string &animationName, const std::string &texturePath);
    void move(sf::Vector2f direction);

    void handleInput(sf::Keyboard::Key attack1, sf::Keyboard::Key attack2, sf::Keyboard::Key attack3, sf::Keyboard::Key attack4);
    Boxer() : state(BoxerState::IDLE), punchDuration(sf::seconds(0.2f)) {}
    const sf::Sprite&  getSprite() const;

    // draw the boxer
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;
    void setPosition(float x, float y);

    void setColor(sf::Color color); // ?
    void setAnimation(const std::string& animationName); //change animation
    

    // action methods
    void jab_right();
    void jab_left();
    void hook();
    void uppercut();
    void block();
    void dodge();
    void take_damage(int amount);
    bool isPunching() const { return state == BoxerState::ATTACKING; }
    
    // Methods managing actions
    void enqueue_action(Action action);
    void update(const sf::Vector2f& opponentPosition);

    // methods K.O.
    void increase_ko_probability(int amount);
    bool attempt_knockout();
    bool is_knocked_out() const;
    void check_for_technical_ko();

    // access methods
    const std::string& get_name() const;
    int get_stamina() const;
    int get_lucky_in_punch() const;
    int get_defense() const;
    int get_speed() const;

    private:
    std::string name;
    int stamina;
    int lucky_in_punch;
    int defense;    
    int speed;
    int ko_probability; 
    bool knocked_out;   

    sf::CircleShape head; //?

    BoxerState state;  // manage state
    sf::Clock punchClock;
    sf::Time punchDuration;
    std::queue<Action> action_queue;  // action queue
    float time_accumulated;           // accumulated time
    float action_interval;


    //test
    sf::Sprite boxerSprite_;
    std::map<std::string, sf::Texture> animations_; // Animations
    
};
