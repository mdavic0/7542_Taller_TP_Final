#include "Idf.h"

Idf::Idf() : Weapon(30, 20, 50) {}

void Idf::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}