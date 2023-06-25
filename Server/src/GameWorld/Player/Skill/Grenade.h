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
        uint8_t damage;

    protected:
        bool available;
        double reloadingClock;
        std::pair<int16_t, int16_t> position;
        std::pair<int16_t, int16_t> movement_direction;
        uint8_t velocity;
        std::shared_ptr<Collidable> collidable;
        double elapsedTime;
        // TODO: ADD EXPLOSION TIME CONFIG

    public:
        Grenade(TypeGrenade typeGrenade, uint8_t damage, std::pair<int16_t, int16_t> position);
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
        virtual ~Grenade();

    private:
        void move();
        void setMovementDirection(bool right);
        void stopMovementDirection();
};


#endif //LEFT4DEAD_GRENADE_H
