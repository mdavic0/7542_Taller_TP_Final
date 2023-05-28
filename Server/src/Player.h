#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include "common_type_operator.h"
#include "common_move.h"

class Player {
    private:
        TypeOperator typeOperator;
        uint8_t life;
        uint8_t fell_down;
        std::pair<uint16_t, uint16_t> position;
        std::pair<uint16_t, uint16_t> movement_direction;
        //Weapon; delega al arma el ataque
    public:
        Player(TypeOperator typeOperator);
        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void applyStep();
        std::pair<uint16_t, uint16_t>& getPosition();
        TypeOperator& getTypeOperator();

    private:
        void move();
};


#endif //LEFT4DEAD_PLAYER_H
