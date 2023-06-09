#include "IDFPlayer.h"

#include <utility>

IDFPlayer::IDFPlayer(std::pair<int16_t, int16_t>& position,
                     std::shared_ptr<Collidable> collidable) :
    Player(TypeOperator::operator_idf, CF::idf_health, CF::idf_velocity,
           std::make_shared<Idf>(), position, std::move(collidable)) {}

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
