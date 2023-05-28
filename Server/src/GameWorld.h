#ifndef LEFT4DEAD_GAMEWORLD_H
#define LEFT4DEAD_GAMEWORLD_H
#include <map>
#include "Player.h"
#include "common_snapshot.h"
#include "common_move.h"

class GameWorld {
    private:
        int players_amount;
        std::map<TypeOperator, Player> players;
    public:
    GameWorld();
    void addPlayer(TypeOperator id);
    void deletePlayer(TypeOperator id);

    void updateMovementDirection(Event event, TypeOperator id, MoveTo direction);
    void simulateStep();
    Snapshot* getSnapshot();
};


#endif //LEFT4DEAD_GAMEWORLD_H
