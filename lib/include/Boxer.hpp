#include <string>

class Boxer 
{
public:
    // Constructor
    Boxer(const std::string& name);

    // Métodos de acción
    void jab_right();
    void jab_left();
    void block();
    void dodge();
    void take_damage(int amount);
    
    // Métodos para K.O.
    void increase_ko_probability(int amount);
    bool attempt_knockout();
    bool is_knocked_out() const;
    void check_for_technical_ko();

    // Métodos de acceso
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
    int ko_probability;  // Atributo agregado para la probabilidad de K.O.
    bool knocked_out;    // Atributo agregado para rastrear si el boxeador está noqueado
};
