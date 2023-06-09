#include "Idf.h"

Idf::Idf() : Weapon(CF::idf_damage,
                    CF::idf_rate,
                    CF::idf_capacity) {}

void Idf::shoot(bool right) {
    if (activated) {
        if (right) {
            //atacar a los q tan a la derecha...
        } else {
            //atacar a los que tan a la izq
        }
    }
}
