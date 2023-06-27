#include "Idf.h"

Idf::Idf() : Weapon(CF::idf_damage,
                    CF::idf_rate,
                    CF::idf_capacity),
                    burstFiredBullets(0), burstEnded(false), scope(CF::idf_scope) {}

bool Idf::shoot(std::shared_ptr<Collidable> &player, const bool& right,
           std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
           const double& stepTime) {
    if (not activated) {
        return false;
    }
    this->rateClock += stepTime;
    this->shootingClock += stepTime;

    if (rateClock >= CF::idf_rate_time and burstFiredBullets < CF::idf_rate) {
        if (right) {
            shootRight(player, infecteds);
        } else {
            shootLeft(player, infecteds);
        }

        burstFiredBullets++;
        if (burstFiredBullets >= CF::idf_rate) {
            burstEnded = true;
        }
        this->rateClock = 0;
        this->totalFiredBullets++;
    }

    if (shootingClock >= CF::idf_rate_time * CF::idf_rate) {
        if (burstFiredBullets >= CF::idf_rate and burstEnded) {
            this->munition--;
            burstEnded = false;
        }
        if (shootingClock >= (CF::idf_rate_time * CF::idf_rate) + CF::idf_burst_delay) {
            shootingClock = 0;
            burstFiredBullets = 0;
        }
        return false;
    }
    return true;
}


bool Idf::reload(const double& stepTime) {
    this->reloadingClock += stepTime;
    if (reloadingClock >= CF::idf_reload_time) {
        this->munition = CF::idf_capacity;
        this->reloadingClock = 0;
        return true;
    }
    return false;
}

void Idf::shootRight(std::shared_ptr<Collidable> &player,
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

void Idf::shootLeft(std::shared_ptr<Collidable> &player,
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

float Idf::calculateDamage(const float& distance) {
    return this->damage - (distance*this->scope) ;
}