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
    // Constructor
    Boxer(const std::string& name);

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

};
