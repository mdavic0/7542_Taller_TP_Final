#include "Witch.h"
#include <utility>
#include "Defines.h"


Witch::Witch(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_witch ,id, CF::witch_health,
                      CF::witch_velocity, CF::witch_damage, position,
                      std::move(collidable)) {}

void Witch::specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->specialAtackActivated) {
        this->scream(infecteds);
    }
}

void Witch::scream(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->target != nullptr and not angry) {
        for (auto& infected : infecteds) {
            // makes all infected follow the player
            infected.second->setTarget(this->target);
        }
        this->velocity += ANGRY_WITCH_SPEED_INCREMENT;
        this->angry = true;
    }
}

Witch::~Witch() = default;
