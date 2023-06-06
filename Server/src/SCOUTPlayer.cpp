#include "SCOUTPlayer.h"

SCOUTPlayer::SCOUTPlayer() : Player(TypeOperator::operator_scout,
                                    200,
                                    8,
                                    std::make_shared<Scout>()) {}

void SCOUTPlayer::specialAtack(Event event) {
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

void SCOUTPlayer::throwGrenade() {

}

void SCOUTPlayer::throwSmoke() {

}

SCOUTPlayer::~SCOUTPlayer() {

}
