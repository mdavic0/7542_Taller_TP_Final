#include "IDFPlayer.h"

IDFPlayer::IDFPlayer() : Player(TypeOperator::operator_idf,
                                150,
                                15,
                                std::make_shared<Idf>()) {}

void IDFPlayer::specialAtack(Event event) {
    switch (event) {
        case Event::event_throw_grenade:
            // lanzar granada wacho
            this->throwGrenade();
        case Event::event_throw_smoke:
            // tirar la de humo
            this->throwSmoke();
        default:
            break;
    }
}

void IDFPlayer::throwGrenade() {

}

void IDFPlayer::throwSmoke() {

}

IDFPlayer::~IDFPlayer() {

}
