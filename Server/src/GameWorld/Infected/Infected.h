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
#include "Player.h"

class Player;

class Infected {
    private:
        TypeInfected typeInfected;
        uint8_t id;

        int8_t life;
        uint8_t velocity;
        uint8_t damage;

        State state;

        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;

        std::shared_ptr<Collidable> collidable;

        bool alive;

        std::shared_ptr<Player> target;
    public:
        Infected(TypeInfected typeInfected, uint8_t id, uint8_t life,
                 uint8_t velocity, uint8_t damage,
                 std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);

        void applyStep(std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                       std::map<uint8_t, std::shared_ptr<Player>>& players);
        std::shared_ptr<Collidable>& getCollidable();
        void applyDamage(const int& amount);
        bool isAlive();

        std::pair<int16_t, int16_t>& getPosition();
        TypeInfected& getTypeInfected();
        State& getState();
        uint8_t& getId();

        virtual ~Infected() = default;

    private:
        void move(std::map<uint8_t, std::shared_ptr<Collidable>>& collidables);
        void atack();
        virtual void specialAtack(Event event) = 0;
        bool isIntoHostilRange(std::shared_ptr<Player> player);
        void setTarget(std::map<uint8_t, std::shared_ptr<Player>>& players);
        void setMovementDirection(MoveTo direction);
        void stopMovementDirection(MoveTo direction);
        void setMovementDirection();
        void stopMovementDirection();
};


#endif //LEFT4DEAD_INFECTED_H
