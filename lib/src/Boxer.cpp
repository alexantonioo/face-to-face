#include "boxer.hpp"
#include <cstdlib> 
#include <iostream>
#include <queue>
#include <functional>

// Constructor
Boxer::Boxer(const std::string& name) 
    : name(name), stamina(100), lucky_in_punch(10), defense(10), speed(10),
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f) {
    head.setRadius(25);
    head.setFillColor(sf::Color::White); 
    head.setPosition(200, 200); // inicial position
      }

Boxer::Boxer(sf::Color color) 
    : name("Default Boxer"), stamina(100), lucky_in_punch(10), defense(10), speed(10), 
      ko_probability(0), knocked_out(false), state(BoxerState::IDLE), time_accumulated(0.0f), action_interval(1.0f) {
    head.setRadius(25);
    head.setFillColor(color); 
    head.setPosition(200, 200); // inicial position
}


// action methods
void Boxer::jab_right() 
{
    std::cout << name << " throws a right jab" << std::endl;
    stamina -= 5;
    increase_ko_probability(3);
    state = BoxerState::ATTACKING;
}

void Boxer::jab_left()
    {
    std::cout << name << " throws a left jab." << std::endl;
    stamina -= 4;  // maybe lowest stamina 
    increase_ko_probability(3);
    state = BoxerState::ATTACKING;
}

void Boxer::hook() 
    {
    std::cout << name << " throws a hook." << std::endl;
    stamina -= 7;  
    increase_ko_probability(5);  
    state = BoxerState::ATTACKING;
}

void Boxer::uppercut() 
    {
    std::cout << name << " throws a uppercut." << std::endl;
    stamina -= 8;  
    increase_ko_probability(6);  
    state = BoxerState::ATTACKING;
}

void Boxer::block() 
{
    std::cout << name << " blocking." << std::endl;
    defense += 10;
    state = BoxerState::BLOCKING;
}

void Boxer::dodge() 
{
    std::cout << name << " try to dodge" << std::endl;
    if (rand() % 100 < speed) {
        std::cout << name << " successfully dodged!" << std::endl;
    }   
    else 
    {
        std::cout << name << " failed dodge" << std::endl;
    }
    state = BoxerState::DODGING;
}

void Boxer::take_damage(int amount) 
{
    if (defense > 0) {
        amount -= defense / 2;
        defense = 0;
        }
    
    if (amount > 0) {
        stamina -= amount;
        std::cout << name << " took " << amount << " damage" << std::endl;
        } 
    
    else {
        std::cout << name << " blocked all the damage!" << std::endl;
    }

    check_for_technical_ko();
    state = BoxerState::TAKING_DAMAGE;
}

void Boxer::enqueue_action(Action action) 
    {
    action_queue.push(action);
}

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
        return true;  // K.O. successful
    }
    return false;  // not K.O.
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


void Boxer::move(sf::Vector2f direction) {
    head.move(direction);
}

void Boxer::draw(sf::RenderWindow& window) {
    window.draw(head);
}

sf::FloatRect Boxer::getBounds() const {
    return head.getGlobalBounds();
}

void Boxer::setPosition(float x, float y) {
    head.setPosition(x, y);
}

void Boxer::setColor(sf::Color color) {
    head.setFillColor(color);
}