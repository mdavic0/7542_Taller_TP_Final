#ifndef LEFT4DEAD_GRENADE_H
#define LEFT4DEAD_GRENADE_H

#include <cstdint>
#include "Infected.h"
#include "TypeGrenade.h"
#include <map>
#include <memory>
#include <utility>


class Infected;
class Player;

class Grenade {
    private:
        TypeGrenade typeGrenade;
        uint16_t id;

    protected:
        uint8_t damage;
        bool available;
        double reloadingClock;
        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;
        uint8_t velocity;
        std::shared_ptr<Collidable> collidable;
        double elapsedTime;
        double explosionClock;
        std::pair<int16_t, int16_t> finalPosition;
        double movementClock;
        bool moving;
        bool readyToExplode;
        bool hasExploded;

    public:
        Grenade(const TypeGrenade& typeGrenade, const uint16_t& id, const uint8_t& damage,
                const std::pair<int16_t, int16_t>& position);
        // aplica mov, incrementa el explosion clock, una vez que explota aplica danios
        virtual void applyStep(std::map<uint16_t, std::shared_ptr<Player>>& players,
                       std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                       const double& stepTime) = 0;
        // hace calculo de posicion final y la activa
        virtual void throwGrenade(const std::pair<int16_t, int16_t>& position,
                                  const double& elapsedTime, const bool& right) = 0;
        std::pair<int16_t, int16_t>& getPosition();
        bool isAvailable();
        bool exploded();
        TypeGrenade getTypeGrenade();
        void setId(const uint16_t& id);
        uint16_t& getId();
        virtual ~Grenade();

    protected:
        void move(const double& stepTime);
        virtual void explode(std::map<uint16_t, std::shared_ptr<Player>> &players,
                             std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                             const double& stepTime) = 0;
        void setMovementDirection(const bool& right);
        void stopMovementDirection();
        void calculateFinalPosition(const bool& right, const double& elapsedTime);
};


#endif //LEFT4DEAD_GRENADE_H
