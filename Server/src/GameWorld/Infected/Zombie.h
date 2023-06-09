#ifndef LEFT4DEAD_ZOMBIE_H
#define LEFT4DEAD_ZOMBIE_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"
#include "TypeInfected.h"


class Zombie : public Infected {
    public:
        Zombie(uint8_t id, std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~Zombie() override;

    private:
        void biteSomeone();
};


#endif //LEFT4DEAD_ZOMBIE_H
