#include "Grenade.h"
#include "Defines.h"
#include "Configuration.h"

Grenade::Grenade(TypeGrenade typeGrenade, uint8_t id, uint8_t damage, std::pair<int16_t, int16_t> position) :
    typeGrenade(typeGrenade), id(id), damage(damage), available(true), reloadingClock(0),
    position(position), movement_direction({0,0}), velocity(0),
    collidable(std::make_shared<Collidable>(0, position, 5, 5)),
    elapsedTime(0), explosionClock(0), finalPosition({0, 0}), movementClock(0),
    moving(false), readyToExplode(false), hasExploded(false) {}


void Grenade::move(double stepTime) {
    if (this->moving and movementClock <= elapsedTime) {
        this->movementClock += stepTime;
        this->position.first += movement_direction.first + movement_direction.first * (velocity * stepTime);
        this->position.second += movement_direction.second + movement_direction.second * (velocity * stepTime);
        this->collidable->updatePosition(this->position);
        if (movementClock >= elapsedTime) {
            this->stopMovementDirection();
            movementClock = 0;
            this->readyToExplode = true;
        }
    }
}

void Grenade::setMovementDirection(bool right) {
    this->moving = true;
    if (right) {
        this->movement_direction = {1, 0};
    } else {
        this->movement_direction = {-1, 0};
    }
}

void Grenade::stopMovementDirection() {
    this->moving = false;
    this->movement_direction = {0, 0};
}

std::pair<int16_t, int16_t> &Grenade::getPosition() {
    return this->position;
}

bool Grenade::isAvailable() {
    return this->available;
}

bool Grenade::exploded() {
    return this->hasExploded;
}

TypeGrenade Grenade::getTypeGrenade() {
    return typeGrenade;
}

void Grenade::calculateFinalPosition(bool right, double time) {
    // x(t) = xi + v * t;
    if (right) {
        finalPosition = {this->position.first + (this->velocity * time) + GRENADE_DAMAGE_RANGE,
                         this->position.second};
    } else {
        finalPosition = {this->position.first - (this->velocity * time) - GRENADE_DAMAGE_RANGE,
                         this->position.second};
    }
}

void Grenade::setId(uint8_t anId) {
    this->id = anId;
}

uint8_t Grenade::getId() {
    return this->id;
}

Grenade::~Grenade() = default;
