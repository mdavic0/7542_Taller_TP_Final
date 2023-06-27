#include "Jumper.h"

Jumper::Jumper(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
            Infected(TypeInfected::infected_jumper , id, CF::jumper_health,
                     CF::jumper_velocity, CF::jumper_damage, position,
                     std::move(collidable)) {}

void Jumper::specialAtack(const Event& event) {

}

void Jumper::jumpOnSomeone() {

}

Jumper::~Jumper() {

}

