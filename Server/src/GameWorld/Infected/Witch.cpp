#include "Witch.h"
#include <utility>

Witch::Witch(uint8_t id, std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(id, CF::witch_health, CF::witch_velocity,
                      CF::witch_damage, position, std::move(collidable)) {}

void Witch::specialAtack(Event event) {

}

void Witch::scream() {

}

Witch::~Witch() {

}
