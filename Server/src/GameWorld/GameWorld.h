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
        uint16_t players_amount;
        std::map<uint16_t, std::shared_ptr<Player>> players;
        TypeGame type;
        uint8_t map; // id of the ui map generated
        uint8_t rounds;

        // All the gameWorld collidables (can be Infecteds, Players, Obstacles, Map limits...)
        std::map<uint16_t, std::shared_ptr<Collidable>> collidables;

        uint16_t infectedId;
        std::map<uint16_t, std::shared_ptr<Infected>> infecteds;

        uint16_t obsacleId;
        std::map<uint16_t, std::shared_ptr<Obstacle>> obstacles;
        bool ended;

        InfectedFactory infectedFactory;
        RespawnController RC;

        ObstacleFactory obstacleFactory;

        PlayerFactory playerFactory;
        std::list<uint16_t> deadPlayersId;

        std::list<std::shared_ptr<Grenade>> grenades;
        std::list<std::shared_ptr<BlitzAtack>> blitzAtacks;

        TypeDifficulty difficulty;

        std::list<std::shared_ptr<Grenade>> postExplosionGrenades;
        std::list<std::shared_ptr<BlitzAtack>> postExplosionBlitz;

        uint16_t mapLimitId;

    public:
        GameWorld(const TypeGame& type, const TypeDifficulty& difficulty);
        uint16_t addPlayer(const TypeOperator& op);
        void deletePlayer(const uint16_t& id);

        void updateMovementDirection(const Event& event, const uint16_t& id, const MoveTo& direction);
        void updateShootingState(const Event& event, const uint16_t& id);
        void updateReloadingState(const Event& event, const uint16_t& id);
        void updateSkillState(const Event& event, const uint16_t& id);

        /*
         * Simula un tiempito en el 'gameworld'.
         * Este tiempito lo que va a hacer es hacer que falte menos
         * para poder lanzar una grandada, que los jugadores se muevan,
         * todos los eventos que tienen que ver con el tiempo.
         */
        void simulateStep(const double& stepTime);
        std::shared_ptr<Snapshot> getSnapshot(const bool& first);
        std::vector<StatsDto> getStats();
        bool isEnded();
        void reanimatePlayer(const Event& event, const uint16_t& id);

        // Cheats
        void finishGame(const Event& event, const uint16_t& id);
        void applySuperSpeed(const Event& event, const uint16_t& id);
        void killInfecteds(const Event& event, const uint16_t& id);
        void makeInmortal(const Event& event, const uint16_t& id);

    private:
        void generateInfecteds();
        void generateObstacles();
        void generateMapLimits();
        TypeObstacle generateObstacleType();
        int generateMapType();

        void simulatePlayersStep(const double& stepTime);
        void simulateInfectedStep(const double& stepTime);
        void simulateGrenadeStep(const double& stepTime);
        void simulateBlitzAtackStep(const double& stepTime);
        void simulatePostExplosionGrenadesStep(const double& stepTime);
        bool allPlayersAreDead();
        void simulatePostExplosionBlitz(const double& stepTime);
        void updateRounds();
};


#endif //LEFT4DEAD_GAMEWORLD_H
