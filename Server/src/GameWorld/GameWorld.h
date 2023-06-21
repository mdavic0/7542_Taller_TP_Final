#ifndef LEFT4DEAD_GAMEWORLD_H
#define LEFT4DEAD_GAMEWORLD_H

#include <map>
#include "Player.h"
#include "Snapshot.h"
#include "Move.h"
#include "TypeGame.h"
#include <memory>
#include "IDFPlayer.h"
#include "SCOUTPlayer.h"
#include "P90Player.h"
#include "Collidable.h"
#include "Defines.h"
#include "Infected.h"
#include "Zombie.h"
#include "Spear.h"
#include "Witch.h"
#include "Jumper.h"
#include "Venom.h"
#include "Obstacle.h"
#include "Tire.h"
#include "Crater.h"
#include "InfectedFactory.h"
#include "RespawnController.h"
#include "ObstacleFactory.h"
#include "PlayerFactory.h"

class GameWorld {
    private:
        uint8_t players_amount;
        std::map<uint8_t, std::shared_ptr<Player>> players;
        TypeGame type;
        uint8_t map;

        // All the gameWorld collidables (can be Infecteds, Players, Obstacles...)
        std::map<uint8_t, std::shared_ptr<Collidable>> collidables;

        uint8_t infectedId;
        std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

        uint8_t obsacleId;
        std::map<uint8_t, std::shared_ptr<Obstacle>> obstacles;
        bool ended;

        InfectedFactory infectedFactory;
        RespawnController RC;

        ObstacleFactory obstacleFactory;

        PlayerFactory playerFactory;

    public:
        GameWorld(const TypeGame& type);
        uint8_t addPlayer(TypeOperator op);
        void deletePlayer(uint8_t id);

        void updateMovementDirection(Event event, uint8_t id, MoveTo direction);
        void updateShootingState(Event event, uint8_t id);
        void simulateStep();
        std::shared_ptr<Snapshot> getSnapshot(bool first);
        std::shared_ptr<Snapshot> getStats();
        bool isEnded();

    private:
        void generateInfecteds();
        void generateObstacles();
        TypeObstacle generateObstacleType();
        int generateMapType();
};


#endif //LEFT4DEAD_GAMEWORLD_H
