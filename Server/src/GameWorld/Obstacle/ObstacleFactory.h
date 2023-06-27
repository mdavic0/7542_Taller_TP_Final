#ifndef LEFT4DEAD_OBSTACLEFACTORY_H
#define LEFT4DEAD_OBSTACLEFACTORY_H

#include "Obstacle.h"
#include "Tire.h"
#include "Crater.h"
#include "RespawnController.h"

class ObstacleFactory {

    public:
        std::shared_ptr<Obstacle>
        getObstacle(const TypeObstacle& obstacle, const uint16_t& obstacleId,
                std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                 RespawnController& RC);

    private:
        std::shared_ptr<Tire>
        createTire(const uint16_t& obstacleId,
                     std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                      RespawnController& RC);

        std::shared_ptr<Crater>
        createCrater(const uint16_t& obstacleId,
                    std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);
};


#endif //LEFT4DEAD_OBSTACLEFACTORY_H
