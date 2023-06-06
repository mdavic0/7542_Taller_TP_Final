#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include "TypeOperator.h"
#include "Move.h"
#include "State.h"
#include "Event.h"
#include "Weapon.h"
#include <memory>

class Player {
    private:
        TypeOperator typeOperator;
        State state;
        uint8_t life;
        uint8_t fell_down;
        std::pair<uint16_t, uint16_t> position;
        std::pair<uint16_t, uint16_t> movement_direction;
        uint8_t velocity;
        std::shared_ptr<Weapon> weapon;

    public:
        explicit Player(TypeOperator typeOperator);
        Player(TypeOperator typeOperator,
               uint8_t life,
               uint8_t velocity,
               std::shared_ptr<Weapon> weapon);
        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void applyStep();
        std::pair<uint16_t, uint16_t>& getPosition();
        TypeOperator& getTypeOperator();
        State& getState();
        uint8_t& getHealth();
        virtual ~Player() = default;
    private:
        void move();
        virtual void specialAtack(Event event) = 0;
};


#endif //LEFT4DEAD_PLAYER_H
