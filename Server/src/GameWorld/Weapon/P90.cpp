#include "P90.h"

P90::P90() : Weapon(CF::p90_damage,
                    CF::p90_rate,
                    CF::p90_capacity),
                    burstFiredBullets(0), burstEnded(false), scope(CF::p90_scope) {}

bool P90::shoot(std::shared_ptr<Collidable> &player, const bool& right,
                std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                const double& stepTime) {
    if (not activated) {
        return false;
    }
    this->rateClock += stepTime;
    this->shootingClock += stepTime;

    if (rateClock >= CF::p90_rate_time and burstFiredBullets < CF::p90_rate) {
        if (right) {
            shootRight(player, infecteds);
        } else {
            shootLeft(player, infecteds);
        }

        burstFiredBullets++;
        if (burstFiredBullets >= CF::p90_rate) {
            burstEnded = true;
        }
        this->rateClock = 0;
        this->totalFiredBullets++;
    }

    if (shootingClock >= CF::p90_rate_time * CF::p90_rate) {
        if (burstFiredBullets >= CF::p90_rate and burstEnded) {
            this->munition--;
            burstEnded = false;
        }
        if (shootingClock >= (CF::p90_rate_time * CF::p90_rate) + CF::p90_burst_delay) {
            shootingClock = 0;
            burstFiredBullets = 0;
        }
        return false;
    }
    return true;
}

bool P90::reload(const double& stepTime) {
    this->reloadingClock += stepTime;
    if (reloadingClock >= CF::p90_reload_time) {
        this->munition = CF::p90_capacity;
        this->reloadingClock = 0;
        return true;
    }
    return false;
}

void P90::shootRight(std::shared_ptr<Collidable> &player,
                     std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    for (auto &infected : infecteds) {
        if (player->isAlignedRight(infected.second->getCollidable())) {
            infected.second->applyDamage(calculateDamage(player->rightDistance(infected.second->getCollidable())));
            if (!infected.second->isAlive()) {
                this->kills++;
            }
        }
    }
}
void P90::shootLeft(std::shared_ptr<Collidable> &player,
                    std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    for (auto &infected : infecteds) {
        if (player->isAlignedLeft(infected.second->getCollidable())) {
            infected.second->applyDamage(calculateDamage(player->leftDistance(infected.second->getCollidable())));
            if (!infected.second->isAlive()) {
                this->kills++;
            }
        }
    }
}

double P90::calculateDamage(const double& distance) {
    return this->damage - (distance*this->scope);
}
