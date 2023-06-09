#include "Zombie.h"

Zombie::Zombie(uint8_t id, std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
        Infected(id, CF::zombie_health, CF::zombie_velocity,
                 CF::zombie_damage, position, std::move(collidable)) {}

void Zombie::specialAtack(Event event) {

}

void Zombie::biteSomeone() {

}

Zombie::~Zombie() {

}
