#include "Venom.h"

Venom::Venom(uint8_t id, std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_venom ,id, CF::venom_health,
                      CF::venom_velocity, CF::venom_damage, position,
                      std::move(collidable)) {}

void Venom::specialAtack(Event event) {

}

void Venom::throwVenom() {

}

Venom::~Venom() {

}
