#ifndef LEFT4DEAD_CRATER_H
#define LEFT4DEAD_CRATER_H
#include "TypeObstacle.h"
#include "Obstacle.h"

class Crater : public Obstacle {
public:
    Crater(uint8_t id, std::pair<int16_t, int16_t>& position,
         std::shared_ptr<Collidable> collidable);
    ~Crater() override;
};


#endif //LEFT4DEAD_CRATER_H
