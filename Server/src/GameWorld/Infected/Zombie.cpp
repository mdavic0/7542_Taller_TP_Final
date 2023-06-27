#include "Zombie.h"

Zombie::Zombie(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
        Infected(TypeInfected::infected_zombie ,id, CF::zombie_health,
                 CF::zombie_velocity, CF::zombie_damage, position,
                 std::move(collidable)) {}

void Zombie::specialAtack(const Event& event) {

}

void Zombie::biteSomeone() {

}

Zombie::~Zombie() {

}
