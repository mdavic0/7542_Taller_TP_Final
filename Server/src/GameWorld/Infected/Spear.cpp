#include "Spear.h"
#include "Defines.h"


Spear::Spear(const uint16_t id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_spear ,id, CF::spear_health,
                      CF::spear_velocity, CF::spear_damage, position,
                      std::move(collidable)) {}

void Spear::specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->specialAtackActivated) {
        this->jumpAndAtack();
    }
}

void Spear::jumpAndAtack() {
    if (this->state != State::hability and not angry) {
        this->state = State::hability;
        this->velocity += SPEAR_HABILITY_SPEED;
        this->angry = true;
    }
}

Spear::~Spear() = default;
