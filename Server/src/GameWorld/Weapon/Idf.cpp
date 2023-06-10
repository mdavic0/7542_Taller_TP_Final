#include "Idf.h"

Idf::Idf() : Weapon(CF::idf_damage,
                    CF::idf_rate,
                    CF::idf_capacity) {}

void Idf::shoot(std::shared_ptr<Collidable>& player, bool right,
                std::map<int, std::shared_ptr<Infected>>& infecteds) {
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
