#ifndef LEFT4DEAD_INFECTED_H
#define LEFT4DEAD_INFECTED_H
#include <cstdint>
#include <utility>
#include <memory>
#include "Move.h"
#include "State.h"
#include "Event.h"
#include "Collidable.h"
#include "TypeInfected.h"

class Infected {
    private:
        TypeInfected typeInfected;
        int id;

        int8_t life;
        uint8_t velocity;
        uint8_t damage;

        State state;

        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;

        std::shared_ptr<Collidable> collidable;

        bool alive;
    public:
        Infected(TypeInfected typeInfected, int id, uint8_t life,
                 uint8_t velocity, uint8_t damage,
                 std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);

        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void applyStep(std::map<int, std::shared_ptr<Collidable>>& collidables);
        std::shared_ptr<Collidable>& getCollidable();
        void applyDamage(const int& amount);
        bool isAlive();

        std::pair<int16_t, int16_t>& getPosition();
        TypeInfected& getTypeInfected();
        State& getState();
        int& getId();

        virtual ~Infected() = default;

    private:
        void move(std::map<int, std::shared_ptr<Collidable>>& collidables);
        void atack();
        virtual void specialAtack(Event event) = 0;
};


#endif //LEFT4DEAD_INFECTED_H
