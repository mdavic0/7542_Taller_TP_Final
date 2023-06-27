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
        uint16_t id;

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
        Infected(const TypeInfected& typeInfected, const uint16_t& id, const uint8_t& life,
                 const uint8_t& velocity, const uint8_t& damage,
                 const std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);

        void applyStep(const std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                       const std::map<uint16_t, std::shared_ptr<Player>>& players);
        std::shared_ptr<Collidable>& getCollidable();
        void applyDamage(const int& amount);
        void applySpeedReduction(const double& speedReduction);
        bool isAlive();

        std::pair<int16_t, int16_t>& getPosition();
        TypeInfected& getTypeInfected();
        State& getState();
        uint16_t& getId();

        virtual ~Infected() = default;

    private:
        void move(const std::map<uint16_t, std::shared_ptr<Collidable>>& collidables);
        void atack();
        virtual void specialAtack(const Event& event) = 0;
        bool isIntoHostilRange(const std::shared_ptr<Player>& player);
        void setTarget(const std::map<uint16_t, std::shared_ptr<Player>>& players);
        void setMovementDirection(const MoveTo& direction);
        void stopMovementDirection(const MoveTo& direction);
        void setMovementDirection();
        void stopMovementDirection();
};


#endif //LEFT4DEAD_INFECTED_H
