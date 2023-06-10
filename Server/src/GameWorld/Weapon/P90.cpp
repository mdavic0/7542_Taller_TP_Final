#include "P90.h"

P90::P90() : Weapon(CF::p90_damage,
                    CF::p90_rate,
                    CF::p90_capacity) {}

#include <iostream>
void P90::shoot(std::shared_ptr<Collidable>& player, bool right,
                std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
            for (auto &infected : infecteds) {
                if (player->isAlignedRight(infected.second->getCollidable())) {
                    std::cout << "Hay un infectado alineado la derecha! Le disparo\n";
                    infected.second->applyDamage(this->damage);
                }
            }
        } else {
            //atacar a los que tan a la izq
            for (auto &infected : infecteds) {
                if (player->isAlignedLeft(infected.second->getCollidable())) {
                    std::cout << "Hay un infectado alineado la izquierda! Le disparo\n";
                    infected.second->applyDamage(this->damage);
                }
            }
        }
    }
}
