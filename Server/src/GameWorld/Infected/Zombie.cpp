#include "Zombie.h"

Zombie::Zombie(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
        Infected(TypeInfected::infected_zombie ,id, CF::zombie_health,
                 CF::zombie_velocity, CF::zombie_damage, position,
                 std::move(collidable)) {}

void Zombie::specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->specialAtackActivated) {
        this->biteSomeone();
    }
}

void Zombie::biteSomeone() {
    this->angry = true;
}

Zombie::~Zombie() = default;
