#include "Infected.h"

#include <utility>

Infected::Infected(uint8_t id, uint8_t life, uint8_t velocity, uint8_t damage,
                   std::pair<int16_t, int16_t> &position,
                   std::shared_ptr<Collidable> collidable) : id(id), life(life),
                   velocity(velocity), damage(damage), state(State::idle),
                   position(position), movement_direction(0,0),
                   collidable(std::move(collidable)), alive(true) {}

void Infected::setMovementDirection(MoveTo direction) {
    switch (direction) {
        // Por sdl el eje "y" va hacia abajo
        case MoveTo::move_up:
            movement_direction.second = -1;
            break;
        case MoveTo::move_down:
            movement_direction.second = 1;
            break;
        case MoveTo::move_left:;
            movement_direction.first = -1;
            break;
        case MoveTo::move_right:
            movement_direction.first = 1;
            break;
        default:
            break;
    }
    if (this->movement_direction.first != 0 or
        this->movement_direction.second != 0) {
        this->state = State::moving;
    }
}

void Infected::stopMovementDirection(MoveTo direction) {
    switch (direction) {
        case MoveTo::move_up:
            movement_direction.second = 0;
            break;
        case MoveTo::move_down:
            movement_direction.second = 0;
            break;
        case MoveTo::move_left:
            movement_direction.first = 0;
            break;
        case MoveTo::move_right:
            movement_direction.first = 0;
            break;
        default:
            break;
    }
    if (this->movement_direction.first == 0 and
        this->movement_direction.second == 0) {
        this->state = State::idle;
    }
}

void Infected::move(std::map<int, std::shared_ptr<Collidable>> &collidables) {
    if (not this->collidable->collidesWith(collidables)) {
        this->position.first += movement_direction.first + movement_direction.first * (velocity / 10);
        this->position.second += movement_direction.second + movement_direction.second * (velocity / 10);
        this->collidable->updatePosition(this->position);
    }
    if (this->collidable->collidesWith(collidables)) {
        this->position.first -= movement_direction.first + movement_direction.first * (velocity / 10);
        this->position.second -= movement_direction.second + movement_direction.second * (velocity / 10);
        this->collidable->updatePosition(this->position);
    }
}

void Infected::atack() {

}

void Infected::applyStep(std::map<int, std::shared_ptr<Collidable>> &collidables) {
    this->move(collidables);
    this->atack();
}

std::shared_ptr<Collidable> &Infected::getCollidable() {
    return this->collidable;
}

void Infected::applyDamage(const int &amount) {
    this->life -= amount;
    if (this->life <= 0) {
        this->alive = false;
    }
}

bool Infected::isAlive() {
    return this->alive;
}

