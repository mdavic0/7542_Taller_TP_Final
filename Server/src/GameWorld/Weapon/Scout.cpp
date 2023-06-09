#include "Scout.h"

Scout::Scout() : Weapon(CF::scout_damage,
                        CF::scout_rate,
                        CF::scout_capacity) {}

void Scout::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}
