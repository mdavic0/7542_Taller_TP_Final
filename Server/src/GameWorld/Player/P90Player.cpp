#include "P90Player.h"

#include <utility>

P90Player::P90Player(std::pair<uint16_t, uint16_t>& position,
                     std::shared_ptr<Collidable> collidable) :
    Player(TypeOperator::operator_p90, 140, 20,
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
