#include "OperatorDto.h"

StOperator::StOperator(const uint16_t& id, const TypeOperator& type, const State& state,
        const std::pair<int16_t, int16_t>& position, const int16_t& health, const uint8_t& munition,
        const bool& grenadeAvailable, const bool& smokeAvailable) :
        id(id), type(type), state(state), position(position), health(health), munition(munition),
        grenadeAvailable(grenadeAvailable), smokeAvailable(smokeAvailable) {}

uint16_t StOperator::getId() const {
    return id;
}

TypeOperator StOperator::getTypeOperator() const {
    return type;
}

State StOperator::getState() const {
    return state;
}

std::pair<int16_t, int16_t> StOperator::getPosition() const {
    return position;
}

int16_t StOperator::getHealth() const {
    return health;
}

uint8_t StOperator::getMunition() const {
    return munition;
}

bool StOperator::isGrenadeAvailable() const {
    return grenadeAvailable;
}

bool StOperator::isSmokeAvailable() const {
    return smokeAvailable;
}