#include "SCOUTPlayer.h"

#include <utility>

SCOUTPlayer::SCOUTPlayer(const std::pair<int16_t, int16_t>& position,
                         std::shared_ptr<Collidable> collidable) :
        Player(TypeOperator::operator_scout, CF::scout_health,
               CF::scout_velocity,std::make_shared<Scout>(),
                       position, std::move(collidable)),
        grenade(std::make_shared<ExplosiveGrenade>(position, 0)),
        grenadeElapsedTime(0), throwingGrenade(false),
        smoke(std::make_shared<SmokeGrenade>(position, 0)),
        smokeElapsedTime(0), throwingSmoke(false) {}


void SCOUTPlayer::setSkillState(const Event& event) {
    if (this->state == State::injure or
        this->state == State::recharge or
        this->state == State::atack or
        this->state == State::stop_hability) {
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

void SCOUTPlayer::stopSkillState(const Event& event) {
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

void SCOUTPlayer::specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                               std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                               const double& stepTime) {
    if (this->state == State::stop_hability) {
        this->stopSkillCLock += stepTime;
    }

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

void SCOUTPlayer::throwGrenade(std::list<std::shared_ptr<Grenade>>& grenades,
                               const double& stepTime) {
    grenadeElapsedTime += stepTime;
    if (this->state == State::stop_hability and stopSkillCLock >= CF::stop_skill_time) {
        this->grenade->setId(grenades.size());
        grenades.push_back(grenade);
        this->grenade->throwGrenade(position, grenadeElapsedTime, lookingRight);
        grenadeElapsedTime = 0;
        stopSkillCLock = 0;
        throwingGrenade = false;
        this->state = State::idle;
    }
}

void SCOUTPlayer::throwSmoke(std::list<std::shared_ptr<Grenade>>& grenades,
                             const double& stepTime) {
    smokeElapsedTime += stepTime;
    if (this->state == State::stop_hability and stopSkillCLock >= CF::stop_skill_time) {
        this->smoke->setId(grenades.size());
        grenades.push_back(smoke);
        this->smoke->throwGrenade(position, smokeElapsedTime, lookingRight);
        smokeElapsedTime = 0;
        stopSkillCLock = 0;
        throwingSmoke = false;
        this->state = State::idle;
    }
}

SCOUTPlayer::~SCOUTPlayer() = default;
