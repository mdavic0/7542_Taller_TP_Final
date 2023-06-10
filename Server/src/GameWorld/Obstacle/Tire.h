#ifndef LEFT4DEAD_TIRE_H
#define LEFT4DEAD_TIRE_H
#include "TypeObstacle.h"
#include "Obstacle.h"

class Tire : public Obstacle {
    public:
        Tire(uint8_t id, std::pair<int16_t, int16_t>& position,
             std::shared_ptr<Collidable> collidable);
        ~Tire() override;
};


#endif //LEFT4DEAD_TIRE_H
