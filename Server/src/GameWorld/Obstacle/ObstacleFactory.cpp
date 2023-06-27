#include "ObstacleFactory.h"
#include <memory>
#include "Defines.h"


std::shared_ptr<Obstacle> ObstacleFactory::getObstacle(const TypeObstacle& obstacle, const uint16_t& obstacleId,
                                                       std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                                        RespawnController &RC) {
    switch (obstacle) {
        case TypeObstacle::obstacle_tire:
            return createTire(obstacleId, collidables, RC);
        case TypeObstacle::obstacle_crater:
            return createCrater(obstacleId, collidables, RC);
        default:
            return createTire(obstacleId, collidables, RC);
    }
}

std::shared_ptr<Tire>
ObstacleFactory::createTire(const uint16_t &obstacleId, std::map<uint16_t,
                            std::shared_ptr<Collidable>> &collidables,
                             RespawnController &RC) {
    std::pair<int16_t, int16_t> position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            (int)obstacleId,position, TIRE_WIDTH, TIRE_HEIGHT);

    collidables.insert({obstacleId, collidable});

    return std::make_shared<Tire>(obstacleId, position, collidable);
}

std::shared_ptr<Crater>
ObstacleFactory::createCrater(const uint16_t &obstacleId, std::map<uint16_t,
                              std::shared_ptr<Collidable>> &collidables,
                               RespawnController &RC) {
    std::pair<int16_t, int16_t> position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            (int)obstacleId,position,CRATER_WIDTH, CRATER_HEIGHT);

    collidables.insert({obstacleId, collidable});

    return std::make_shared<Crater>(obstacleId, position, collidable);
}
