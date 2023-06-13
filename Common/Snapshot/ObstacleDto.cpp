#include "ObstacleDto.h"

ObstacleDto::ObstacleDto(const uint8_t& id, const TypeObstacle& type,
        const std::pair<int16_t, int16_t>& position) : id(id), type(type), position(position) {}

uint8_t ObstacleDto::getId() const {
    return id;
}

TypeObstacle ObstacleDto::getTypeObstacle() const {
    return type;
}

std::pair<int16_t, int16_t> ObstacleDto::getPosition() const {
    return position;
}
