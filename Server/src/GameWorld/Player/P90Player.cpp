#include "P90Player.h"

#include <utility>

P90Player::P90Player(std::pair<int16_t, int16_t>& position,
                     std::shared_ptr<Collidable> collidable) :
    Player(TypeOperator::operator_p90, CF::p90_health, CF::p90_velocity,
           std::make_shared<P90>(), position, std::move(collidable)) {}

void P90Player::specialAtack(Event event) {
    switch (event) {
        case Event::event_blitz_atack:
            // se lanza el bombardeo aereo wach
            // state::grenade
            this->blitz();
        default:
            break;
    }
}

void P90Player::blitz() {

}

P90Player::~P90Player() {

}

void P90Player::revive() {
    this->life = CF::p90_health / 2;
    this->state = State::idle;
}
