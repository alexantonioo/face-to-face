#include "boxer.hpp"
#include <cstdlib> // Para std::rand()
#include <iostream>
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
    std::cout << name << " lanza un jab con la derecha." << std::endl;
    stamina -= 5;
    increase_ko_probability(3);
}

void Boxer::jab_left() 
{
    std::cout << name << " lanza un jab con la izquierda." << std::endl;
    stamina -= 4;  // Un jab con la izquierda puede costar menos stamina
    increase_ko_probability(3);
}

void Boxer::block() 
{
    std::cout << name << " está bloqueando." << std::endl;
    defense += 10;
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
}

void Boxer::take_damage(int amount) 
{
    if (defense > 0) 
    {
        amount -= defense / 2;  
        defense = 0;  
    }
    
    if (amount > 0) 
    {
    stamina -= amount;  
        std::cout << name << " recibió " << amount << " de daño." << std::endl;
    } 
    else 
    {
    std::cout << name << " bloqueó todo el daño!" << std::endl;
    }

    check_for_technical_ko();
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