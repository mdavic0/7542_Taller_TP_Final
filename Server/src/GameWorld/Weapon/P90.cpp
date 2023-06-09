#include "P90.h"

P90::P90() : Weapon(CF::p90_damage,
                    CF::p90_rate,
                    CF::p90_capacity) {}

void P90::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}
