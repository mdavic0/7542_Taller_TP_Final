#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include "TypeOperator.h"
#include "Move.h"

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
        void set_movement_direction(MoveTo direction);
        void apply_step();
        std::pair<uint16_t, uint16_t>& get_position();
        TypeOperator& get_type_operator();

    private:
        void move();
};


#endif //LEFT4DEAD_PLAYER_H
