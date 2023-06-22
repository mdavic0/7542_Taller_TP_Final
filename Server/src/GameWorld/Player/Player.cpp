#include "Player.h"

#include <utility>
#include "Defines.h"

Player::Player(TypeOperator typeOperator) : typeOperator(typeOperator),
    state(State::idle), life(100), fell_down(0), position(0,0),
    movement_direction(0,0), velocity(1), weapon(), lookingRight(true),
    alive(true) {}

Player::Player(TypeOperator typeOperator, uint8_t life, uint8_t velocity,
    std::shared_ptr<Weapon> weapon, std::pair<int16_t, int16_t>& position,
    std::shared_ptr<Collidable> collidable) :
    typeOperator(typeOperator), state(State::idle), life(life), fell_down(0),
    position(position), movement_direction(0,0), velocity(velocity),
    weapon(std::move(weapon)), lookingRight(true), collidable(std::move(collidable)),
    alive(true) {}

void Player::setMovementDirection(MoveTo direction) {
    if (this->state == State::injure) {
        return;
    }

    switch (direction) {
        // Por sdl el eje "y" va hacia abajo
        case MoveTo::move_up:
            movement_direction.second = -1;
            break;
        case MoveTo::move_down:
            movement_direction.second = 1;
            break;
        case MoveTo::move_left:
            lookingRight = false;
            movement_direction.first = -1;
            break;
        case MoveTo::move_right:
            lookingRight = true;
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
    if (this->state != State::injure and
        this->movement_direction.first == 0 and
        this->movement_direction.second == 0) {
        this->state = State::idle;
    }
}

void Player::setShootingState() {
    if (this->state == State::injure) {
        return;
    }

    this->movement_direction = {0, 0};
    this->state = State::atack;
    this->weapon->activate();
}

void Player::stopShootingState() {
    if (this->state == State::injure) {
        return;
    }

    this->state = State::idle;
    this->weapon->deactivate();
}

void Player::applyStep(std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                       std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) {
    this->move(collidables);
    this->shoot(infecteds);
}

std::pair<int16_t, int16_t>& Player::getPosition() {
    return this->position;
}

TypeOperator& Player::getTypeOperator() {
    return this->typeOperator;
}

State& Player::getState() {
    return this->state;
}

int8_t& Player::getHealth() {
    return this->life;
}

uint8_t& Player::getMunition() {
    return weapon->getMunition();
}

std::shared_ptr<Collidable> &Player::getCollidable() {
    return this->collidable;
}

void Player::move(std::map<uint8_t, std::shared_ptr<Collidable>>& collidables) {
    if (this->state != State::injure) {
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
}

void Player::shoot(std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) {
    if (this->state != State::injure) {
        this->weapon->shoot(this->collidable, this->lookingRight, infecteds);
    }
}

void Player::applyDamage(const int &amount) {
    this->life -= amount;

    if (this->life <= 0) {
        this->life = 0;
        this->movement_direction = {0, 0};
        this->state = State::injure;
        this->fell_down++;

        if (this->fell_down >= FELL_DOWN_LIMIT) {
            this->alive = false;
        }
    }
}

bool Player::isAlive() {
    return this->alive;
}

bool Player::isFellDown() {
    return this->state == State::injure;
}
