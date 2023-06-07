#include "P90.h"

P90::P90() : Weapon(20, 10, 30) {}

void P90::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}