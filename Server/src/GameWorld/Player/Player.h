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
#include "Collidable.h"
#include "Infected.h"

class Player {
    private:
        TypeOperator typeOperator;
        State state;
        uint8_t life;
        uint8_t fell_down;
        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;
        uint8_t velocity;
        std::shared_ptr<Weapon> weapon;
        bool lookingRight;
        std::shared_ptr<Collidable> collidable;
    public:
        explicit Player(TypeOperator typeOperator);
        Player(TypeOperator typeOperator,uint8_t life,uint8_t velocity,
               std::shared_ptr<Weapon> weapon, std::pair<int16_t,
               int16_t>& position, std::shared_ptr<Collidable> collidable);
        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void setShootingState();
        void stopShootingState();
        void applyStep(std::map<int, std::shared_ptr<Collidable>>& collidables,
                       std::map<uint8_t, std::shared_ptr<Infected>>& infecteds);
        std::pair<int16_t, int16_t>& getPosition();
        TypeOperator& getTypeOperator();
        State& getState();
        uint8_t& getHealth();
        virtual ~Player() = default;
    private:
        void move(std::map<int, std::shared_ptr<Collidable>>& collidables);
        void shoot(std::map<uint8_t, std::shared_ptr<Infected>>& infecteds);
        virtual void specialAtack(Event event) = 0;
};


#endif //LEFT4DEAD_PLAYER_H
