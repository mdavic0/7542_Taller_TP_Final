#include "BlitzAtack.h"
#include "Configuration.h"
#include "Defines.h"


BlitzAtack::BlitzAtack() : damage(CF::blitz_damage), available(true),
        reloadingClock(0), blitzClock(0), readyToBlitz(false), end(false) {}

void BlitzAtack::applyStep(std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                           double stepTime) {
    if (not available) {
        this->blitz(infecteds, stepTime);
        this->reloadingClock += stepTime;
        if (reloadingClock >= CF::blitz_recharge) {
            this->reloadingClock = 0;
            available = true;
        }
    }
}

void BlitzAtack::throwBlitz(std::pair<int16_t, int16_t>& pos) {
    if (this->available) {
        this->position = pos;
        this->collidable = std::make_shared<Collidable>(0, position, 5, 5);
        this->reloadingClock = 0;
        this->blitzClock = 0;
        this->available = false;
    }
}

bool BlitzAtack::isAvailable() {
    return this->available;
}

bool BlitzAtack::ended() {
    return this->end;
}

void BlitzAtack::blitz(std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                       double stepTime) {
    this->blitzClock += stepTime;
    if (blitzClock >= CF::blitz_animation_time) {
        this->readyToBlitz = true;
    }
    if (this->readyToBlitz) {
        for (auto &infected : infecteds) {
            if (infected.second->getCollidable()->
                isCloseTo(this->collidable, BLITZ_ATTACK_IMPACT_RANGE)) {
                infected.second->applyDamage(this->damage);
            }
            this->end = true;
            this->readyToBlitz = false;
            this->blitzClock = 0;
        }
    }
}
