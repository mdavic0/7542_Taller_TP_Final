#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include "TypeOperator.h"
#include "Move.h"

// TODO: USAR POLIMORFISMO YA QUE HAY != TIPOS DE PLAYER
class Player {
    private:
        TypeOperator typeOperator;
        uint8_t life;
        uint8_t fell_down;
        std::pair<uint16_t, uint16_t> position;
        std::pair<uint16_t, uint16_t> movement_direction;
        //Weapon; delega al arma el ataque
        // TODO: WAPON TAMBIEN SERA POLIMORFICA
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
