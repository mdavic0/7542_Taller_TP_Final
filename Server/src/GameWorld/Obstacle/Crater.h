#ifndef LEFT4DEAD_CRATER_H
#define LEFT4DEAD_CRATER_H
#include "TypeObstacle.h"
#include "Obstacle.h"

class Crater : public Obstacle {
public:
    Crater(const uint16_t& id, const std::pair<int16_t, int16_t>& position,
         std::shared_ptr<Collidable> collidable);
    ~Crater() override;
};


#endif //LEFT4DEAD_CRATER_H
