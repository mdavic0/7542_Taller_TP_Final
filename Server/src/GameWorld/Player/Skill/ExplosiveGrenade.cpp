#include "ExplosiveGrenade.h"
#include "Defines.h"


ExplosiveGrenade::ExplosiveGrenade(std::pair<int16_t, int16_t> position, uint8_t id) :
    Grenade(TypeGrenade::grenade_explosive, id,CF::grenade_damage, position) {}

void ExplosiveGrenade::applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                                 std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                                 double stepTime) {
    if (not available) {
        this->move(stepTime);
        this->explode(players, infecteds, stepTime);
        this->reloadingClock += stepTime;
        if (reloadingClock >= CF::grenade_recharge) {
            this->reloadingClock = 0;
            available = true;
        }
    }
}


void ExplosiveGrenade::throwGrenade(std::pair<int16_t, int16_t>& position,
                                    double elapsedTime, bool right) {
    if (this->available) {
        if (right) {
            this->position = {position.first + GRENADE_DAMAGE_RANGE, position.second};
        } else {
            this->position = {position.first - GRENADE_DAMAGE_RANGE, position.second};
        }
        this->collidable->updatePosition(this->position);
        this->elapsedTime = elapsedTime;
        this->setMovementDirection(right);
        this->calculateFinalPosition(right, elapsedTime);
        this->movementClock = 0;
        this->reloadingClock = 0;
        this->available = false;
        this->hasExploded = false;
    }
}

void ExplosiveGrenade::explode(std::map<uint8_t, std::shared_ptr<Player>> &players,
                               std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                               double stepTime) {
    if (this->readyToExplode) {
        explosionClock += stepTime;
        if (explosionClock >= CF::grenade_explosion_time) {
            for (auto &player : players) {
                if (player.second->getCollidable()->
                    isCloseTo(this->collidable, GRENADE_DAMAGE_RANGE)) {
                    player.second->applyDamage(this->damage);
                }
            }

            for (auto &infected : infecteds) {
                if (infected.second->getCollidable()->
                    isCloseTo(this->collidable, GRENADE_DAMAGE_RANGE)) {
                    infected.second->applyDamage(this->damage);
                }
            }
            this->hasExploded = true;
            this->readyToExplode = false;
            this->explosionClock = 0;
        }
    }
}

ExplosiveGrenade::~ExplosiveGrenade() = default;
