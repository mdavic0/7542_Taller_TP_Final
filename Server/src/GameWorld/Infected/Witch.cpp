#include "Witch.h"
#include <utility>

Witch::Witch(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_witch ,id, CF::witch_health,
                      CF::witch_velocity, CF::witch_damage, position,
                      std::move(collidable)) {}

void Witch::specialAtack(const Event& event) {

}

void Witch::scream() {

}

Witch::~Witch() {

}
