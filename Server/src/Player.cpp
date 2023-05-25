#include "Player.h"

Player::Player(TypeOperator typeOperator) : typeOperator(typeOperator),
    life(100), fell_down(0), position(0,0), movement_direction(0,0) {
    // weapon(TypeOperator)
}

void Player::set_movement_direction(MoveTo direction) {
    switch (direction) {
        case MoveTo::move_idle:
            movement_direction = {0,0};
        case MoveTo::move_up:
            movement_direction.second = 1;
        case MoveTo::move_down:
            movement_direction.second = -1;
        case MoveTo::move_left:
            movement_direction.first = -1;
        case MoveTo::move_right:
            movement_direction.first = 1;
    }
}

void Player::apply_step() {
    this->move();
    //this->attack();
}

std::pair<uint16_t, uint16_t>& Player::get_position() {
    return this->position;
}

TypeOperator& Player::get_type_operator() {
    return this->typeOperator;
}

void Player::move() {
    this->position.first += this->movement_direction.first;
    this->position.second += this->movement_direction.second;
}
