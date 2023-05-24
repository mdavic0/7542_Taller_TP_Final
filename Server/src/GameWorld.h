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
    void add_player(TypeOperator id);
    void delete_player(TypeOperator id);

    void update_movement_direction(TypeOperator id, MoveTo direction);
    void simulate_step();
    Snapshot* get_snapshot();
};


#endif //LEFT4DEAD_GAMEWORLD_H
