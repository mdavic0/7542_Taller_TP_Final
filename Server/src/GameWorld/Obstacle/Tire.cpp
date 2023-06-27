#include "Tire.h"

#include <utility>

Tire::Tire(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
           std::shared_ptr<Collidable> collidable) :
        Obstacle(TypeObstacle::obstacle_tire , id, position,
                 std::move(collidable)) {}

Tire::~Tire() = default;
