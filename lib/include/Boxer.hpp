#include <string>
#include <queue>
#include <functional>
#include <SFML/Graphics.hpp>

    
    using Action = std::function<void()>;

    // Definimos los estados posibles del boxeador**
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
    Boxer(const std::string& name);  // Constructor que acepta un nombre
    Boxer(sf::Color color);           // Constructor que acepta un color
    Boxer(const std::string& name, sf::Color color); // Constructor que acepta nombre y color


// Mover el boxeador en cierta dirección
    void move(sf::Vector2f direction);

    // Dibujar el boxeador en la ventana
    void draw(sf::RenderWindow& window);

    // Obtener los límites del boxeador (para las colisiones)
    sf::FloatRect getBounds() const;

    // Posicionar al boxeador en una ubicación específica
    void setPosition(float x, float y);

    void setColor(sf::Color color); // Método para establecer el color
    //void draw(sf::RenderWindow& window); // Método para dibujar el boxeado


    // Métodos de acción**
    void jab_right();
    void jab_left();
    void hook();
    void uppercut();
    void block();
    void dodge();
    void take_damage(int amount);
    
    // Métodos para gestionar acciones
    void enqueue_action(Action action);
    void update(float delta_time);

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

    sf::CircleShape head;

    BoxerState state;  // Añadimos esta variable para gestionar el estado
    std::queue<Action> action_queue;  // Cola para las acciones
    float time_accumulated;           // Tiempo acumulado
    float action_interval;

};
