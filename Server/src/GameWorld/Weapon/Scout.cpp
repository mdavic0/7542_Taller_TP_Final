#include "Scout.h"

Scout::Scout() : Weapon(CF::scout_damage,
                        CF::scout_rate,
                        CF::scout_capacity),
                        burstFiredBullets(0), burstEnded(false) {}

bool Scout::shoot(std::shared_ptr<Collidable> &player, bool right,
                  std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                  double stepTime) {
    if (not activated) {
        return false;
    }
    this->rateClock += stepTime;
    this->shootingClock += stepTime;

    if (rateClock >= CF::scout_rate_time and burstFiredBullets < CF::scout_rate) {
        if (right) {
            shootRight(player, infecteds);
        } else {
            shootLeft(player, infecteds);
        }

        burstFiredBullets++;
        if (burstFiredBullets >= CF::scout_rate) {
            burstEnded = true;
        }
        this->rateClock = 0;
        this->totalFiredBullets++;
    }

    if (shootingClock >= CF::scout_rate_time * CF::scout_rate) {
        if (burstFiredBullets >= CF::scout_rate and burstEnded) {
            this->munition--;
            burstEnded = false;
        }
        if (shootingClock >= (CF::scout_rate_time * CF::scout_rate) + CF::scout_burst_delay) {
            shootingClock = 0;
            burstFiredBullets = 0;
        }
        return false;
    }
    return true;
}

bool Scout::reload(double stepTime) {
    this->reloadingClock += stepTime;
    if (reloadingClock >= CF::scout_reload_time) {
        this->munition = CF::scout_capacity;
        this->reloadingClock = 0;
        return true;
    }
    return false;
}

void Scout::shootRight(std::shared_ptr<Collidable> &player,
                     std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) {
    for (auto &infected : infecteds) {
        if (player->isAlignedRight(infected.second->getCollidable())) {
            infected.second->applyDamage(this->damage);
        }
    }
}

void Scout::shootLeft(std::shared_ptr<Collidable> &player,
                    std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) {
    for (auto &infected : infecteds) {
        if (player->isAlignedLeft(infected.second->getCollidable())) {
            infected.second->applyDamage(this->damage);
        }
    }
}
