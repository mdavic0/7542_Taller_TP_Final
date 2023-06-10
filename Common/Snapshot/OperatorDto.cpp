#include "OperatorDto.h"

StOperator::StOperator(const uint8_t& id, const TypeOperator& type, const State& state,
        const std::pair<int16_t, int16_t>& position, const uint8_t& health) : id(id), type(type),
        state(state), position(position), health(health) {}

uint8_t StOperator::getId() const {
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

uint8_t StOperator::getHealth() const {
    return health;
}
