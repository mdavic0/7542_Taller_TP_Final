#include "Player.h"

Player::Player(TypeOperator typeOperator) : typeOperator(typeOperator),
    life(100), fell_down(0), position(0,0), movement_direction(0,0) {
    // weapon(TypeOperator)
}
#include <iostream>
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
}

void Player::stopMovementDirection(MoveTo direction) {
    std::cout << "Seteando direccion\n";
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
    std::cout << "Direccion seteada\n";
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

void Player::move() {
    this->position.first += this->movement_direction.first;
    this->position.second += this->movement_direction.second;
}
