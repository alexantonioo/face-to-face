#include <string>
#include <vector>
#include <unordered_map>
//#include "Timer.hpp"

class Boxer 
{
    private:
        std::string name;
        int health;
        int stamina;
        int strength;
        int defense;    
        int speed;
        int agility;

        std::vector<std::string> current_combo;
        //std::unordered_map<std::string, Timer> cooldowns; ??
        //faltan los atributos del cooldown, los del timer
        //Timer jab_cooldown_timer;       
        //Timer uppercut_cooldown_timer;  

    public:
        Boxer(const std::string& name);

        // Metodos 
        void jab();
        void uppercut();
        void block();
        void dodge();
        void take_damage(int amount);

        // Getters y Setters ??
};
