#include "boxer.hpp"
#include <cstdlib> // Para std::rand()

// Constructor
Boxer::Boxer(const std::string& name) 
    : name(name), stamina(100), lucky_in_punch(10), defense(10), speed(10), 
    ko_probability(0), knocked_out(false)
{
    // Inicialización de otros atributos si es necesario
}

// Métodos de acción
void Boxer::jab_right() 
{
    // Lógica del golpe de derecha
    increase_ko_probability(5);  // Incrementa la probabilidad de K.O.
}

void Boxer::jab_left() 
{
    // Lógica del golpe de izquierda
    increase_ko_probability(5);  // Incrementa la probabilidad de K.O.
}

void Boxer::block() 
{
    // Lógica para bloquear
}

void Boxer::dodge() 
{
    // Lógica para esquivar
}

void Boxer::take_damage(int amount) 
{
    stamina -= amount;
    check_for_technical_ko();  // Verifica si se debe dar K.O. técnico
}

// Métodos para K.O.
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

// Métodos de acceso
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