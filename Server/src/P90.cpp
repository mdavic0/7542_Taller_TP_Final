#include "P90.h"

P90::P90() : Weapon(20, 10, 30) {}

void P90::shoot(Event event) {
    switch (event) {
        case Event::event_shoot_left:
            //atacar a los que tan a la izq
        case Event::event_shoot_right:
            //atacar a los q tan a la derecha...
        default:
            break;
    }
}