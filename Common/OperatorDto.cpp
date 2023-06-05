#include "OperatorDto.h"

StOperator::StOperator(const uint8_t& id, const TypeOperator& type, const State& state,
        const std::pair<uint16_t, uint16_t>& position, const uint8_t& health) : id(id), type(type),
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

std::pair<uint16_t, uint16_t> StOperator::getPosition() const {
    return position;
}

uint8_t StOperator::getHealth() const {
    return health;
}

/*
StOperator::StOperator(StOperator&& other) {
    this->id = other.id;
    this->type = other.type;
    this->state = other.state;
    this->position = other.position;
    this->health = other.health;

    other.id = 0;
    other.type = TypeOperator::operator_idle;
    other.state = State::idle;
    other.position = std::pair<uint16_t, uint16_t> {};
    other.health = 0;
}

StOperator& StOperator::operator=(StOperator&& other) {
    if (this == &other)
        return *this;

    this->id = other.id;
    this->type = other.type;
    this->state = other.state;
    this->position = other.position;
    this->health = other.health;

    other.id = 0;
    other.type = TypeOperator::operator_idle;
    other.state = State::idle;
    other.position = std::pair<uint16_t, uint16_t> {};
    other.health = 0;

    return *this;
}
*/
