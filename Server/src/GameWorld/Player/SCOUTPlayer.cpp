#include "SCOUTPlayer.h"

#include <utility>

SCOUTPlayer::SCOUTPlayer(std::pair<int16_t, int16_t>& position,
                         std::shared_ptr<Collidable> collidable) :
        Player(TypeOperator::operator_scout, CF::scout_health,
               CF::scout_velocity,std::make_shared<Scout>(),
                       position, std::move(collidable)),
        grenade(std::make_shared<ExplosiveGrenade>(position)),
        grenadeElapsedTime(0), throwingGrenade(false),
        smoke(std::make_shared<SmokeGrenade>(position)),
        smokeElapsedTime(0), throwingSmoke(false) {}


void SCOUTPlayer::setSkillState(Event event) {
    if (this->state == State::injure or
        this->state == State::recharge or
        this->state == State::atack) {
        return;
    }

    if (event == Event::event_throw_grenade and
        this->grenade->isAvailable()) {
        grenadeElapsedTime = 0;
        throwingGrenade = true;
    }

    if (event == Event::event_throw_smoke and
        this->smoke->isAvailable()) {
        smokeElapsedTime = 0;
        throwingSmoke = true;
    }

    if (throwingGrenade or throwingSmoke) {
        this->movement_direction = {0, 0};
        this->state = State::hability;
    }
}

void SCOUTPlayer::stopSkillState(Event event) {
    if (this->state == State::injure or
        this->state == State::recharge or
        this->state == State::atack) {
        return;
    }

    if (this->state == State::hability) {
        this->state = State::stop_hability;
    }
}

void SCOUTPlayer::specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                               std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                               double stepTime) {
    if (throwingGrenade and isGrenadeAvailable()) {
        this->throwGrenade(grenades, stepTime);
    }

    if (throwingSmoke and isSmokeAvailable()) {
        this->throwSmoke(grenades, stepTime);
    }
}

void SCOUTPlayer::revive() {
    this->life = CF::scout_health / 2.0;
    this->state = State::idle;
}

bool SCOUTPlayer::isGrenadeAvailable() {
    return this->grenade->isAvailable();
}

bool SCOUTPlayer::isSmokeAvailable() {
    return this->smoke->isAvailable();
}
#include <iostream>
void SCOUTPlayer::throwGrenade(std::list<std::shared_ptr<Grenade>>& grenades,
                               double stepTime) {
    grenadeElapsedTime += stepTime;
    if (this->state == State::stop_hability) {
        grenades.push_back(grenade);
        this->grenade->throwGrenade(position, grenadeElapsedTime, lookingRight);
        std::cout << "Grenade Amount: " + std::to_string(grenades.size()) << std::endl;
        grenadeElapsedTime = 0;
        throwingGrenade = false;
        this->state = State::idle;
    }
}

void SCOUTPlayer::throwSmoke(std::list<std::shared_ptr<Grenade>>& grenades,
                             double stepTime) {
    smokeElapsedTime += stepTime;
    if (this->state == State::stop_hability) {
        grenades.push_back(smoke);
        this->smoke->throwGrenade(position, smokeElapsedTime, lookingRight);
        std::cout << "Grenade Amount: " + std::to_string(grenades.size()) << std::endl;
        smokeElapsedTime = 0;
        throwingSmoke = false;
        this->state = State::idle;
    }
}

SCOUTPlayer::~SCOUTPlayer() = default;
