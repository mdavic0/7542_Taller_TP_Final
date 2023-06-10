#include "EnemyDto.h"

EnemyDto::EnemyDto(const uint8_t& id, const TypeInfected& type, const State& state,
    const std::pair<int16_t, int16_t>& position) : id(id), type(type),
    state(state), position(position) {}

uint8_t EnemyDto::getId() const {
    return id;
}

TypeInfected EnemyDto::getTypeInfected() const {
    return type;
}

State EnemyDto::getState() const {
    return state;
}

std::pair<int16_t, int16_t> EnemyDto::getPosition() const {
    return position;
}
