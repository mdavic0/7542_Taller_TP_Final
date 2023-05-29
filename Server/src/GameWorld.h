#ifndef LEFT4DEAD_GAMEWORLD_H
#define LEFT4DEAD_GAMEWORLD_H
#include <map>
#include "Player.h"
#include "Snapshot.h"
#include "Move.h"

class GameWorld {
    private:
        int players_amount;
        std::map<TypeOperator, Player> players;
        // TODO: VECTOR DE VECTORES DE POSICIONES (EN ORDEN) DE CADA PLAYER /
        //    MONSTRUITO ENEMIGO EN EL GAME (PARA EFECTUAR BIEN EL ATAQUE, YA QUE
        //    ESTE VARIA DEPENDIENDO DE LA DISTANCIA / ENEMIGOS ATRAVEZADOS)
    public:
    GameWorld();
    void addPlayer(TypeOperator id);
    void deletePlayer(TypeOperator id);

    void updateMovementDirection(TypeOperator id, MoveTo direction);
    void simulateStep();
    Snapshot* getSnapshot();
};


#endif //LEFT4DEAD_GAMEWORLD_H
