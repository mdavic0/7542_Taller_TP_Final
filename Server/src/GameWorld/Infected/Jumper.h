#ifndef LEFT4DEAD_JUMPER_H
#define LEFT4DEAD_JUMPER_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"
#include "TypeInfected.h"

class Jumper : public Infected {
    public:
        Jumper(const uint16_t& id, const std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;
        ~Jumper() override;

    private:
        void jumpOnSomeone();
};


#endif //LEFT4DEAD_JUMPER_H
