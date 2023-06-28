#include "Jumper.h"
#include "Defines.h"


Jumper::Jumper(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
            Infected(TypeInfected::infected_jumper , id, CF::jumper_health,
                     CF::jumper_velocity, CF::jumper_damage, position,
                     std::move(collidable)) {}

void Jumper::specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->specialAtackActivated) {
        this->jumpOnSomeone();
    }
}

void Jumper::jumpOnSomeone() {
    if (this->state != State::hability and not angry) {
        this->state = State::hability;
        this->velocity += JUMPER_HABILITY_SPEED;
        this->angry = true;
    }
}

Jumper::~Jumper() = default;
