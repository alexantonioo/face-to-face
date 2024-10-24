#include "boxer.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>

// Constructor
Boxer::Boxer(const std::string& name) 
    : name(name), stamina(100), lucky_in_punch(10), defense(10), speed(10), 
        ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f)
{
    // Inicialización de otros atributos si es necesario
}


// Métodos de acción**
void Boxer::jab_right() 
{
    std::cout << name << " lanza un jab con la derecha." << std::endl;
    stamina -= 5;
    increase_ko_probability(3);
    state = BoxerState::ATTACKING;
}

void Boxer::jab_left()
    {
    std::cout << name << " lanza un jab con la izquierda." << std::endl;
    stamina -= 4;  // Un jab con la izquierda puede costar menos stamina
    increase_ko_probability(3);
    state = BoxerState::ATTACKING;
}

void Boxer::hook() 
<<<<<<< Updated upstream
    {
    std::cout << name << " lanza un hook." << std::endl;
    stamina -= 7;  
    increase_ko_probability(5);  
    state = BoxerState::ATTACKING;
}

void Boxer::uppercut() 
    {
    std::cout << name << " lanza un uppercut." << std::endl;
    stamina -= 8;  
    increase_ko_probability(6);  
    state = BoxerState::ATTACKING;
=======
{
    if (state == BoxerState::IDLE) 
        {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("hook", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/hook.png");

        setAnimation("hook");  
        //FALTA AJUSTAR STAMINA
    }
}

void Boxer::uppercut() 
{
    if (state == BoxerState::IDLE) 
        {  
        state = BoxerState::ATTACKING;
        punchClock.restart();  

        loadAnimation("uppercut", "/mnt/c/Users/alex/Documents/GitHub/face-to-face/assets/images/uppercut.png");

        setAnimation("uppercut");  
    }
>>>>>>> Stashed changes
}

void Boxer::block() 
{
    std::cout << name << " está bloqueando." << std::endl;
    defense += 10;
    state = BoxerState::BLOCKING;
}

bool Boxer::isBlocking() const 
    {
    return state == BoxerState::BLOCKING;  
}

void Boxer::dodge() 

{
    std::cout << name << " intenta esquivar." << std::endl;
    if (rand() % 100 < speed) {
        std::cout << name << " esquivó con éxito!" << std::endl;
    }   
    else 
    {
        std::cout << name << " falló al esquivar." << std::endl;
    }
    state = BoxerState::DODGING;
}

void Boxer::attempt_parry(Boxer& opponent) 
    {
    
    if (state == BoxerState::BLOCKING && opponent.isPunching()) 
        {
        
        sf::Time elapsedTime = punchClock.getElapsedTime();
        
        
        if (elapsedTime.asSeconds() < 0.5f) 
            { 
            state = BoxerState::STUNNED;
            opponent.cancel_attack();
            opponent.setState(BoxerState::STUNNED);
            //setAnimation("parry"); 
        }
    }
}

void Boxer::cancel_attack() 
    {
    
    if (isPunching()) 
        {
        state = BoxerState::IDLE;
        action_queue = std::queue<Action>();

          //empty the queue

    }
}

void Boxer::take_damage(int amount) 
{
    if (defense > 0) {
        amount -= defense / 2;
        defense = 0;
        }
    
    if (amount > 0) {
        stamina -= amount;
        std::cout << name << " recibió " << amount << " de daño." << std::endl;
        } 
    
    else {
        std::cout << name << " bloqueó todo el daño!" << std::endl;
    }

    check_for_technical_ko();
    state = BoxerState::TAKING_DAMAGE;
}


// Sistema de eventos**
void Boxer::enqueue_action(Action action) 
    {
    action_queue.push(action);
}

<<<<<<< Updated upstream
=======
void Boxer::update() 
    {
>>>>>>> Stashed changes

// Método update para procesar las acciones en cola
void Boxer::update(float delta_time) 
    {
    time_accumulated += delta_time;

        if (time_accumulated >= action_interval && !action_queue.empty()) 
            {
        
        action_queue.front()();
        action_queue.pop();

        time_accumulated = 0.0f;
        }
}

<<<<<<< Updated upstream

// Métodos para K.O.**
=======
void Boxer::setState(BoxerState newState) 
    {
    state = newState;
}

>>>>>>> Stashed changes
void Boxer::increase_ko_probability(int amount) 
{
    ko_probability += amount;
}

bool Boxer::attempt_knockout() 
{
    int chance = std::rand() % 100;
    if (chance < ko_probability) 
    {
        knocked_out = true;
        return true;  // K.O. exitoso
    }
    return false;  // No se da el K.O.
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
    }
}


// Métodos de acceso**
const std::string& Boxer::get_name() const 
    {
        return name;
    }

int Boxer::get_stamina() const 
{
    return stamina;
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