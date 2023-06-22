#include "Weapon.h"

Weapon::Weapon() : damage(0), rate(0), capacity(0), activated(false),
    munition(0), totalFiredBullets(0), reloadingClock(0) {}

Weapon::Weapon(uint8_t damage, uint8_t rate, uint8_t capacity) :
    damage(damage), rate(rate), capacity(capacity), activated(false),
    munition(capacity), totalFiredBullets(0), reloadingClock(0) {}

Weapon::~Weapon() = default;

void Weapon::activate() {
    this->activated = true;
}

void Weapon::deactivate() {
    this->activated = false;
}

uint8_t& Weapon::getMunition() {
    return munition;
}