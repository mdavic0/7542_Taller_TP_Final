#ifndef LEFT4DEAD_JUMPER_H
#define LEFT4DEAD_JUMPER_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"


class Jumper : public Infected {
    public:
        Jumper(uint8_t id, std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~Jumper() override;

    private:
        void jumpOnSomeone();
};


#endif //LEFT4DEAD_JUMPER_H
