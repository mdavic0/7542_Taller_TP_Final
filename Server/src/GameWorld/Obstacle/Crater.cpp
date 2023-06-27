#include "Crater.h"

Crater::Crater(const uint16_t& id, const std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
        Obstacle(TypeObstacle::obstacle_crater , id, position,
                 std::move(collidable)) {}

Crater::~Crater() = default;
