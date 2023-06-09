#include "Jumper.h"

Jumper::Jumper(uint8_t id, std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
            Infected(id, CF::jumper_health, CF::jumper_velocity,
                 CF::jumper_damage, position, std::move(collidable)) {}

void Jumper::specialAtack(Event event) {

}

void Jumper::jumpOnSomeone() {

}

Jumper::~Jumper() {

}

