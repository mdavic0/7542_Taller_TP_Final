#include "Tire.h"

#include <utility>

Tire::Tire(uint8_t id, std::pair<int16_t, int16_t> &position,
           std::shared_ptr<Collidable> collidable) :
        Obstacle(TypeObstacle::obstacle_tire , id, position,
                 std::move(collidable)) {}

Tire::~Tire() = default;
