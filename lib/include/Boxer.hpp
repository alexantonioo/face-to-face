#include <string>
#include <queue>
#include <functional>

    
    using Action = std::function<void()>;

    // Definimos los estados posibles del boxeador**
    enum class BoxerState 
        {
    IDLE,
    ATTACKING,
    BLOCKING,
    DODGING,
    STUNNED,
    TAKING_DAMAGE
    };

class Boxer 
    {
public:
<<<<<<< Updated upstream
    // Constructor
    Boxer(const std::string& name);
=======

    Boxer(const std::string& name);  // Constructor name
    Boxer(sf::Color color);           // Constructor color
    Boxer(const std::string& name, sf::Color color); // Constructor color/name
    Boxer(const std::string& name, const std::string& initialTexturePath);
    void loadTexture(const std::string& animationName, const std::string& texturePath);
    void loadAnimation(const std::string &animationName, const std::string &texturePath);
    void move(sf::Vector2f direction);
>>>>>>> Stashed changes

    // Métodos de acción**
    void jab_right();
    void jab_left();
    void hook();
    void uppercut();
    void block();
    void dodge();
    void take_damage(int amount);
<<<<<<< Updated upstream
=======
    bool isPunching() const { return state == BoxerState::ATTACKING; }
    bool isBlocking() const;
    void attempt_parry(Boxer& opponent);
    void cancel_attack();
>>>>>>> Stashed changes
    
    // Métodos para gestionar acciones
    void enqueue_action(Action action);
<<<<<<< Updated upstream
    void update(float delta_time);
=======
    void update();
    void setState(BoxerState newState);
>>>>>>> Stashed changes

    // Métodos para K.O.**
    void increase_ko_probability(int amount);
    bool attempt_knockout();
    bool is_knocked_out() const;
    void check_for_technical_ko();

    // Métodos de acceso**
    const std::string& get_name() const;
    int get_stamina() const;
    float get_max_stamina() const;
    int get_lucky_in_punch() const;
    int get_defense() const;
    int get_speed() const;

    // Stamina
    void reduce_stamina(float amount);       
    void recover_stamina(float amount);      


    private:
    std::string name;
    float stamina;
    float max_stamina;  
    int lucky_in_punch;
    int defense;    
    int speed;
    int ko_probability; 
    bool knocked_out;   
<<<<<<< Updated upstream

    BoxerState state;  // Añadimos esta variable para gestionar el estado
    std::queue<Action> action_queue;  // Cola para las acciones
    float time_accumulated;           // Tiempo acumulado
=======
    
    
    sf::CircleShape head;

    BoxerState state;  // manage state
    sf::Clock punchClock;
    sf::Time punchDuration;
    std::queue<Action> action_queue;  // action queue
    float time_accumulated;           // accumulated time
>>>>>>> Stashed changes
    float action_interval;

<<<<<<< Updated upstream
=======
    sf::RectangleShape staminaBar;
    
    //test
    sf::Sprite boxerSprite_;
    std::map<std::string, sf::Texture> animations_; // Animations
    
>>>>>>> Stashed changes
};
