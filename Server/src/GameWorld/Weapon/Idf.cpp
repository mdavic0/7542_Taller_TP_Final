#include "Idf.h"

Idf::Idf() : Weapon(CF::idf_damage,
                    CF::idf_rate,
                    CF::idf_capacity) {}

void Idf::shoot(std::shared_ptr<Collidable>& player, bool right,
                std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
            for (auto &infected : infecteds) {
                if (player->isAlignedRight(infected.second->getCollidable())) {
                    infected.second->applyDamage(this->damage);
                }
            }
        } else {
            //atacar a los que tan a la izq
            for (auto &infected : infecteds) {
                if (player->isAlignedLeft(infected.second->getCollidable())) {
                    infected.second->applyDamage(this->damage);
                }
            }
        }
        this->munition--;
        this->totalFiredBullets++;
    }
}

#include <iostream>
bool Idf::reload(double stepTime) {
    this->reloadingClock += stepTime;
    std::cout << std::to_string(reloadingClock) << std::endl;
    if (reloadingClock >= CF::idf_reload_time) {
        this->munition = CF::idf_capacity;
        this->reloadingClock = 0;
        return true;
    }
    return false;
}
