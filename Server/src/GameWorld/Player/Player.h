#ifndef LEFT4DEAD_PLAYER_H
#define LEFT4DEAD_PLAYER_H
#include <cstdint>
#include <utility>
#include <list>
#include "TypeOperator.h"
#include "Move.h"
#include "State.h"
#include "Event.h"
#include "Weapon.h"
#include <memory>
#include "Collidable.h"
#include "Infected.h"
#include "Grenade.h"
#include "BlitzAtack.h"

class Infected;
class Weapon;
class Grenade;
class BlitzAtack;

class Player {
    private:
        TypeOperator typeOperator;
        uint8_t fell_down;
        uint8_t velocity;
        std::shared_ptr<Weapon> weapon;
        std::shared_ptr<Collidable> collidable;
        bool alive;

    protected:
        int8_t life;
        State state;
        std::pair<int16_t, int16_t> movement_direction;
        bool lookingRight;
        std::pair<int16_t, int16_t> position;
        double stopSkillCLock;

    public:
        explicit Player(const TypeOperator& typeOperator);
        Player(const TypeOperator& typeOperator, const uint8_t& life, const uint8_t& velocity,
               std::shared_ptr<Weapon> weapon, const std::pair<int16_t,
               int16_t>& position, std::shared_ptr<Collidable> collidable);
        void setMovementDirection(const MoveTo& direction);
        void stopMovementDirection(const MoveTo& direction);
        void setShootingState();
        void stopShootingState();
        void setReloadingState();
        virtual void setSkillState(const Event& event) = 0;
        virtual void stopSkillState(const Event& event) = 0;
        void applyStep(std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                       std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                       std::list<std::shared_ptr<Grenade>> &grenades,
                       std::list<std::shared_ptr<BlitzAtack>> &blitzAtacks,
                       const double& stepTime);
        std::pair<int16_t, int16_t>& getPosition();
        TypeOperator& getTypeOperator();
        State& getState();

        int8_t& getHealth();
        uint8_t& getMunition();
        uint16_t& getKills();
        uint16_t& getShots();

        virtual bool isGrenadeAvailable() = 0;
        virtual bool isSmokeAvailable() = 0;
        std::shared_ptr<Collidable>& getCollidable();
        void applyDamage(const int& amount);

        bool isAlive();
        bool isFellDown();

        virtual void revive() = 0;

        virtual ~Player() = default;

    private:
        void move(std::map<uint16_t, std::shared_ptr<Collidable>>& collidables);
        void shoot(std::map<uint16_t, std::shared_ptr<Infected>> &infecteds, const double& stepTime);
        void reload(const double& stepTime);
        virtual void specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                                  std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                                  const double& stepTime) = 0;

};


#endif //LEFT4DEAD_PLAYER_H
