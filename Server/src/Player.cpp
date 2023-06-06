#include "Player.h"

#include <utility>

Player::Player(TypeOperator typeOperator) : typeOperator(typeOperator), state(State::idle),
    life(100), fell_down(0), position(0,0), movement_direction(0,0), velocity(1), weapon() {}

Player::Player(TypeOperator typeOperator, uint8_t life, uint8_t velocity,
               std::shared_ptr<Weapon> weapon) : typeOperator(typeOperator),
    state(State::idle), life(life), fell_down(0), position(0,0), movement_direction(0,0),
    velocity(velocity), weapon(std::move(weapon)) {}

void Player::setMovementDirection(MoveTo direction) {
    switch (direction) {
        // Por sdl el eje "y" va hacia abajo
        case MoveTo::move_up:
            movement_direction.second = -1;
            break;
        case MoveTo::move_down:
            movement_direction.second = 1;
            break;
        case MoveTo::move_left:
            movement_direction.first = -1;
            break;
        case MoveTo::move_right:
            movement_direction.first = 1;
            break;
        default:
            break;
    }
    if (this->movement_direction.first != 0 or this->movement_direction.second != 0) {
        this->state = State::moving;
    }
}

void Player::stopMovementDirection(MoveTo direction) {
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
    if (this->movement_direction.first == 0 and this->movement_direction.second == 0) {
        this->state = State::idle;
    }
}

void Player::applyStep() {
    this->move();
    //this->attack();
}

std::pair<uint16_t, uint16_t>& Player::getPosition() {
    return this->position;
}

TypeOperator& Player::getTypeOperator() {
    return this->typeOperator;
}

State& Player::getState() {
    return this->state;
}
uint8_t& Player::getHealth() {
    return this->life;
}

void Player::move() {
    this->position.first += movement_direction.first + movement_direction.first * (velocity / 10);
    this->position.second += movement_direction.second + movement_direction.second * (velocity / 10);
}
