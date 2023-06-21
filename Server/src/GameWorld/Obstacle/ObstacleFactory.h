#ifndef LEFT4DEAD_OBSTACLEFACTORY_H
#define LEFT4DEAD_OBSTACLEFACTORY_H

#include "Obstacle.h"
#include "Tire.h"
#include "Crater.h"
#include "RespawnController.h"

class ObstacleFactory {

    public:
        std::shared_ptr<Obstacle>
        getObstacle(TypeObstacle obstacle, uint8_t& obstacleId,
                std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                RespawnController& RC);

    private:
        std::shared_ptr<Tire>
        createTire(uint8_t& obstacleId,
                     std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);

        std::shared_ptr<Crater>
        createCrater(uint8_t& obstacleId,
                    std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);
};


#endif //LEFT4DEAD_OBSTACLEFACTORY_H
