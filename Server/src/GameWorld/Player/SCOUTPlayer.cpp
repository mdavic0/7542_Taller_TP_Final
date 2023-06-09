#include "SCOUTPlayer.h"

#include <utility>

SCOUTPlayer::SCOUTPlayer(std::pair<int16_t, int16_t>& position,
                         std::shared_ptr<Collidable> collidable) :
    Player(TypeOperator::operator_scout, 200, 8,
           std::make_shared<Scout>(), position, std::move(collidable)) {}

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
