#include "Spear.h"

Spear::Spear(uint8_t id, std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(id, CF::spear_health, CF::spear_velocity,
                      CF::spear_damage, position, std::move(collidable)) {}

void Spear::specialAtack(Event event) {

}

void Spear::throwSpear() {

}

Spear::~Spear() {

}
