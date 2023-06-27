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
#include "Grenade.h"
#include "BlitzAtack.h"


class GameWorld {
    private:
        uint8_t players_amount;
        std::map<uint8_t, std::shared_ptr<Player>> players;
        TypeGame type;
        uint8_t map; // id of the ui map generated
        uint8_t rounds;

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
        std::list<uint8_t> deadPlayersId;

        std::list<std::shared_ptr<Grenade>> grenades;
        std::list<std::shared_ptr<BlitzAtack>> blitzAtacks;

        TypeDifficulty difficulty;

        std::list<std::shared_ptr<Grenade>> postExplosionGrenades;
        std::list<std::shared_ptr<BlitzAtack>> postExplosionBlitz;

    public:
        GameWorld(const TypeGame& type, const TypeDifficulty& difficulty);
        uint8_t addPlayer(TypeOperator op);
        void deletePlayer(uint8_t id);

        void updateMovementDirection(Event event, uint8_t id, MoveTo direction);
        void updateShootingState(Event event, uint8_t id);
        void updateReloadingState(Event event, uint8_t id);
        void updateSkillState(Event event, uint8_t id);

        /*
         * Simula un tiempito en el 'gameworld'.
         * Este tiempito lo que va a hacer es hacer que falte menos
         * para poder lanzar una grandada, que los jugadores se muevan,
         * todos los eventos que tienen que ver con el tiempo.
         */
        void simulateStep(double stepTime);
        std::shared_ptr<Snapshot> getSnapshot(bool first);
        std::vector<StatsDto> getStats();
        bool isEnded();
        void reanimatePlayer(Event event, uint8_t id);
        void finishGame(Event event, uint8_t id);
        void applySuperSpeed(Event event, uint8_t id);

    private:
        void generateInfecteds();
        void generateObstacles();
        TypeObstacle generateObstacleType();
        int generateMapType();

        void simulatePlayersStep(double stepTime);
        void simulateInfectedStep(double stepTime);
        void simulateGrenadeStep(double stepTime);
        void simulateBlitzAtackStep(double stepTime);
        void simulatePostExplosionGrenadesStep(double stepTime);
        bool allPlayersAreDead();
        void simulatePostExplosionBlitz(double stepTime);
        void updateRounds();
};


#endif //LEFT4DEAD_GAMEWORLD_H
