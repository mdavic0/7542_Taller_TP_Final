#include "Weapon.h"

Weapon::Weapon() : damage(0), rate(0), capacity(0) {

}

Weapon::Weapon(uint8_t damage, uint8_t rate, uint8_t capacity) :
    damage(damage), rate(rate), capacity(capacity) {

}

Weapon::~Weapon() {

}
