#ifndef OBSTACLE_DTO_H_
#define OBSTACLE_DTO_H_

#include <utility>
#include <map>
#include <string>
#include "TypeObstacle.h"

class ObstacleDto {
    uint16_t id;
    TypeObstacle type;
    std::pair<int16_t, int16_t> position;
    
    public:

    explicit ObstacleDto(const uint16_t& id, const TypeObstacle& type,
        const std::pair<int16_t, int16_t>& position);

    uint16_t getId() const;

    TypeObstacle getTypeObstacle() const;

    std::pair<int16_t, int16_t> getPosition() const;
};

#endif
