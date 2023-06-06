#include "P90Player.h"

P90Player::P90Player() : Player(TypeOperator::operator_p90,
                                    140,
                                    20,
                                    std::make_shared<P90>()) {}

void P90Player::specialAtack(Event event) {
    switch (event) {
        case Event::event_blitz_atack:
            // se lanza el bombardeo aereo wach
            this->blitz();
        default:
            break;
    }
}

void P90Player::blitz() {

}

P90Player::~P90Player() {

}
