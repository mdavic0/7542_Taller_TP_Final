#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include "TypeOperator.h"
#include "Move.h"
#include "State.h"

// TODO: USAR POLIMORFISMO YA QUE HAY != TIPOS DE PLAYER
class Player {
    private:
        TypeOperator typeOperator;
        State state;
        uint8_t life;
        uint8_t fell_down;
        std::pair<uint16_t, uint16_t> position;
        std::pair<uint16_t, uint16_t> movement_direction;
        //Weapon; delega al arma el ataque
        // TODO: WAPON TAMBIEN SERA POLIMORFICA
    public:
        Player(TypeOperator typeOperator);
        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void applyStep();
        std::pair<uint16_t, uint16_t>& getPosition();
        TypeOperator& getTypeOperator();
        State& getState();
        uint8_t& getHealth();

    private:
        void move();
};


#endif //LEFT4DEAD_PLAYER_H