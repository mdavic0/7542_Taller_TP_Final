#ifndef LEFT4DEAD_BLITZATACK_H
#define LEFT4DEAD_BLITZATACK_H

#include <cstdint>
#include "Infected.h"
#include "TypeGrenade.h"
#include "Collidable.h"
#include <map>
#include <memory>
#include <utility>

class Infected;
class Player;

class BlitzAtack {
    private:
        uint8_t damage;

        bool available;
        double reloadingClock;

        std::pair<int16_t, int16_t> position;

        double blitzClock;
        bool readyToBlitz;
        bool end;

        std::shared_ptr<Collidable> collidable;

    public:
        BlitzAtack();
        void applyStep(std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                       const double& stepTime);
        // Hace calculo de la zona de ataque y lo activa
        void throwBlitz(const std::pair<int16_t, int16_t>& position);
        bool isAvailable();
        bool ended();

    private:
        void blitz(std::map<uint16_t, std::shared_ptr<Infected>> &infecteds,
                   const double& stepTime);
};


#endif //LEFT4DEAD_BLITZATACK_H
