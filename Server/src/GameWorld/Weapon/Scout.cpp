#include "Scout.h"

Scout::Scout() : Weapon(CF::scout_damage,
                        CF::scout_rate,
                        CF::scout_capacity) {}

void Scout::shoot(std::shared_ptr<Collidable>& player, bool right,
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
    }
}
