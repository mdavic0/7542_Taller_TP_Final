#include "Venom.h"

Venom::Venom(const uint8_t& id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_venom ,id, CF::venom_health,
                      CF::venom_velocity, CF::venom_damage, position,
                      std::move(collidable)) {}

void Venom::specialAtack(const Event& event) {

}

void Venom::throwVenom() {

}

Venom::~Venom() {

}
