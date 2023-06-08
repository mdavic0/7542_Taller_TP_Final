#include "Scout.h"

Scout::Scout() : Weapon(60, 1, 20) {}

void Scout::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}