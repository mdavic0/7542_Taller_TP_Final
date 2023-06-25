#include "P90Player.h"

#include <utility>

P90Player::P90Player(std::pair<int16_t, int16_t>& position,
                     std::shared_ptr<Collidable> collidable) :
    Player(TypeOperator::operator_p90, CF::p90_health, CF::p90_velocity,
           std::make_shared<P90>(), position, std::move(collidable)),
    blitz(std::make_shared<BlitzAtack>()) ,throwingBlitzAtack(false) {}


void P90Player::setSkillState(Event event) {
    if (this->state == State::injure or
        this->state == State::recharge or
        this->state == State::atack or
        this->state == State::stop_hability) {
        return;
    }

    if (event == Event::event_throw_grenade and
        this->blitz->isAvailable()) {
        throwingBlitzAtack = true;
        this->movement_direction = {0, 0};
        this->state = State::hability;
    }
}

void P90Player::stopSkillState(Event event) {
    if (this->state == State::injure or
        this->state == State::recharge or
        this->state == State::atack or
        this->state == State::stop_hability) {
        return;
    }

    if (this->state == State::hability) {
        this->state = State::stop_hability;
        stopSkillCLock = 0;
    }
}

void P90Player::specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                             std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                             double stepTime) {
    if (this->state == State::stop_hability) {
        this->stopSkillCLock += stepTime;
    }

    if (throwingBlitzAtack and isGrenadeAvailable()) {
        this->throwBlitzAtack(blitzAtacks);
    }
}

void P90Player::throwBlitzAtack(std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks) {
    if (this->state == State::stop_hability and stopSkillCLock >= CF::blitz_animation_time) {
        blitzAtacks.push_back(blitz);
        this->blitz->throwBlitz(this->position);
        throwingBlitzAtack = false;
        stopSkillCLock = 0;
        this->state = State::idle;
    }
}

void P90Player::revive() {
    this->life = CF::p90_health / 2;
    this->state = State::idle;
}

bool P90Player::isGrenadeAvailable() {
    return this->blitz->isAvailable();
}

bool P90Player::isSmokeAvailable() {
    return false;
}

P90Player::~P90Player() = default;
