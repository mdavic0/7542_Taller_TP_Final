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

class GameWorld {
    private:
        uint8_t players_amount;
        std::map<uint8_t, std::shared_ptr<Player>> players;
        TypeGame type;
        uint8_t map;
        // TODO: VECTOR DE VECTORES DE POSICIONES (EN ORDEN) DE CADA PLAYER /
        //    MONSTRUITO ENEMIGO EN EL GAME (PARA EFECTUAR BIEN EL ATAQUE, YA QUE
        //    ESTE VARIA DEPENDIENDO DE LA DISTANCIA / ENEMIGOS ATRAVEZADOS)
        std::map<uint8_t, std::shared_ptr<Collidable>> collidables;

        uint8_t infectedId;
        std::map<uint8_t, std::shared_ptr<Infected>> infecteds;


    public:
        GameWorld(const TypeGame& type, uint8_t map);
        uint8_t addPlayer(TypeOperator op);
        void deletePlayer(uint8_t id);

        void updateMovementDirection(Event event, uint8_t id, MoveTo direction);
        void updateShootingState(Event event, uint8_t id);
        void simulateStep();
        std::shared_ptr<Snapshot> getSnapshot(bool first);

    private:
        void generateInfecteds();
};


#endif //LEFT4DEAD_GAMEWORLD_H
