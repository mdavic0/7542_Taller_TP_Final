#ifndef LEFT4DEAD_INFECTED_H
#define LEFT4DEAD_INFECTED_H
#include <cstdint>
#include <utility>
#include <memory>
#include "Move.h"
#include "State.h"
#include "Event.h"
#include "Collidable.h"

class Infected {
    private:
        uint8_t id;

        uint8_t life;
        uint8_t velocity;
        uint8_t damage;

        State state;

        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;

        std::shared_ptr<Collidable> collidable;

    public:
        Infected(uint8_t id, uint8_t life, uint8_t velocity, uint8_t damage,
                 std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);

        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void applyStep(std::map<int, std::shared_ptr<Collidable>>& collidables);
        virtual ~Infected() = default;

    private:
        void move(std::map<int, std::shared_ptr<Collidable>>& collidables);
        void atack();
        virtual void specialAtack(Event event) = 0;
};


#endif //LEFT4DEAD_INFECTED_H
