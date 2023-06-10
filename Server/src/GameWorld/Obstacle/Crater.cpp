#include "Crater.h"

Crater::Crater(uint8_t id, std::pair<int16_t, int16_t> &position,
               std::shared_ptr<Collidable> collidable) :
        Obstacle(TypeObstacle::obstacle_crater , id, position,
                 std::move(collidable)) {}

Crater::~Crater() = default;
