#include "Scout.h"

Scout::Scout() : Weapon(60, 1, 20) {}

void Scout::shoot(Event event) {
    switch (event) {
        case Event::event_shoot_left:
            //atacar a los que tan a la izq
        case Event::event_shoot_right:
            //atacar a los q tan a la derecha...
        default:
            break;
    }
}