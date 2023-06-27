#include "Spear.h"

Spear::Spear(const uint16_t id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_spear ,id, CF::spear_health,
                      CF::spear_velocity, CF::spear_damage, position,
                      std::move(collidable)) {}

void Spear::specialAtack(const Event& event) {

}

void Spear::throwSpear() {

}

Spear::~Spear() {

}
