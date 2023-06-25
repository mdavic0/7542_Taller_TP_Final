#include "Grenade.h"

Grenade::Grenade(TypeGrenade typeGrenade, uint8_t damage, std::pair<int16_t, int16_t> position) :
    typeGrenade(typeGrenade), damage(damage), available(true), reloadingClock(0),
    position(position), movement_direction({0,0}), velocity(0),
    collidable(std::make_shared<Collidable>(0, position, 5, 5)) {}

void Grenade::move() {
    this->position.first += movement_direction.first + movement_direction.first * (velocity / 10);
    this->position.second += movement_direction.second + movement_direction.second * (velocity / 10);
    this->collidable->updatePosition(this->position);
}

void Grenade::setMovementDirection(bool right) {
    if (right) {
        this->movement_direction = {1, 0};
    } else {
        this->movement_direction = {-1, 0};
    }
}

void Grenade::stopMovementDirection() {
    this->movement_direction = {0, 0};
}

std::pair<int16_t, int16_t> &Grenade::getPosition() {
    return this->position;
}

bool Grenade::isAvailable() {
    return this->available;
}

bool Grenade::exploded() {
    return false;
}

TypeGrenade Grenade::getTypeGrenade() {
    return typeGrenade;
}

Grenade::~Grenade() = default;
