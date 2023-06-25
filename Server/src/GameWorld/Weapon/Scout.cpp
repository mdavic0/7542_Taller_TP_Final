#include "Scout.h"
#include <algorithm>

Scout::Scout() : Weapon(CF::scout_damage,
                        CF::scout_rate,
                        CF::scout_capacity),
                        burstFiredBullets(0), burstEnded(false), scope(CF::scout_scope),
                        damageDecreaseByEnemy(CF::scout_damage_decrease_by_enemy) {}

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
    int counter = 0;
    for (auto &infected : sortEnemiesRight(infecteds)) {
        if (player->isAlignedRight(infected->getCollidable())) {
            infected->applyDamage(calculateDamage(player->rightDistance(infected->getCollidable()), counter));
            counter++;
        }
    }
}

void Scout::shootLeft(std::shared_ptr<Collidable> &player,
                    std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) {
    int counter = 0;
    for (auto &infected : sortEnemiesLeft(infecteds)) {
        if (player->isAlignedLeft(infected->getCollidable())) {
            infected->applyDamage(calculateDamage(player->leftDistance(infected->getCollidable()), counter));
            counter++;
        }
    }
}

float Scout::calculateDamage(float distance, int& counter) {
    return this->damage - (distance*this->scope) - (counter*this->damageDecreaseByEnemy);
}

std::vector<std::shared_ptr<Infected>> Scout::sortEnemiesRight(const std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) {
    std::vector<std::shared_ptr<Infected>> sortedInfected;

    for (const auto& pair : infecteds) {
        sortedInfected.push_back(pair.second);
    }

    std::sort(sortedInfected.begin(), sortedInfected.end(), [](std::shared_ptr<Infected> obj1, std::shared_ptr<Infected> obj2) {
        return obj1->getCollidable()->getLeftCorner() < obj2->getCollidable()->getLeftCorner();
    });


    return sortedInfected;
}

std::vector<std::shared_ptr<Infected>> Scout::sortEnemiesLeft(const std::map<uint8_t, std::shared_ptr<Infected>> &infecteds) {
    std::vector<std::shared_ptr<Infected>> sortedInfected;

    for (const auto& pair : infecteds) {
        sortedInfected.push_back(pair.second);
    }

    std::sort(sortedInfected.begin(), sortedInfected.end(), [](std::shared_ptr<Infected> obj1, std::shared_ptr<Infected> obj2) {
        return obj1->getCollidable()->getLeftCorner() > obj2->getCollidable()->getLeftCorner();
    });


    return sortedInfected;
}
