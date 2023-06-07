#include "Weapon.h"

Weapon::Weapon() : damage(0), rate(0), capacity(0), activated(false) {

}

Weapon::Weapon(uint8_t damage, uint8_t rate, uint8_t capacity) :
    damage(damage), rate(rate), capacity(capacity), activated(false) {

}

Weapon::~Weapon() {

}

void Weapon::activate() {
    this->activated = true;
}

void Weapon::deactivate() {
    this->activated = false;
}
