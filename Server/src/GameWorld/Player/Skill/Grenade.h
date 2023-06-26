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
        uint8_t id;

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
        Grenade(TypeGrenade typeGrenade, uint8_t id, uint8_t damage,
                std::pair<int16_t, int16_t> position);
        // aplica mov, incrementa el explosion clock, una vez que explota aplica danios
        virtual void applyStep(std::map<uint8_t, std::shared_ptr<Player>>& players,
                       std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                       double stepTime) = 0;
        // hace calculo de posicion final y la activa
        virtual void throwGrenade(std::pair<int16_t, int16_t>& position,
                                  double elapsedTime, bool right) = 0;
        std::pair<int16_t, int16_t>& getPosition();
        bool isAvailable();
        bool exploded();
        TypeGrenade getTypeGrenade();
        void setId(uint8_t id);
        uint8_t getId();
        virtual ~Grenade();

    protected:
        void move(double stepTime);
        virtual void explode(std::map<uint8_t, std::shared_ptr<Player>> &players,
                             std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                             double stepTime) = 0;
        void setMovementDirection(bool right);
        void stopMovementDirection();
        void calculateFinalPosition(bool right, double elapsedTime);
};


#endif //LEFT4DEAD_GRENADE_H
