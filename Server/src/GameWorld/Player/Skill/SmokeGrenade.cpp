#include "SmokeGrenade.h"
#include "Defines.h"


SmokeGrenade::SmokeGrenade(std::pair<int16_t, int16_t> position) :
        Grenade(TypeGrenade::grenade_smoke,  CF::grenade_damage, position),
        speedReduction(CF::smoke_speed_reduction) {}

void SmokeGrenade::applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                             std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                             double stepTime) {
    if (not available) {
        this->move(stepTime);
        this->explode(players, infecteds, stepTime);
        this->reloadingClock += stepTime;
        if (reloadingClock >= CF::smoke_recharge) {
            this->reloadingClock = 0;
            available = true;
        }
    }
}

void SmokeGrenade::throwGrenade(std::pair<int16_t, int16_t>& position,
                                double elapsedTime, bool right) {
    if (this->available) {
        if (right) {
            this->position = {position.first + GRENADE_DAMAGE_RANGE, position.second};
        } else {
            this->position = {position.first - GRENADE_DAMAGE_RANGE, position.second};
        }
        this->elapsedTime = elapsedTime;
        this->setMovementDirection(right);
        this->calculateFinalPosition(right, elapsedTime);
        this->movementClock = 0;
        this->reloadingClock = 0;
        this->available = false;
    }
}

void SmokeGrenade::explode(std::map<uint8_t, std::shared_ptr<Player>> &players,
                           std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                           double stepTime) {
    if (this->readyToExplode) {
        explosionClock += stepTime;
        if (explosionClock >= CF::smoke_explosion_time) {
            for (auto &infected : infecteds) {
                if (infected.second->getCollidable()->
                        isCloseTo(this->collidable, GRENADE_DAMAGE_RANGE)) {
                    infected.second->applySpeedReduction(this->speedReduction);
                }
            }
            this->hasExploded = true;
            this->readyToExplode = false;
            this->explosionClock = 0;
        }
    }
}

SmokeGrenade::~SmokeGrenade() = default;
