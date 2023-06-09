#ifndef LEFT4DEAD_WITCH_H
#define LEFT4DEAD_WITCH_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"

class Witch : public Infected {
    public:
        Witch(uint8_t id, std::pair<int16_t, int16_t>& position,
              std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~Witch() override;

    private:
        void scream();
};


#endif //LEFT4DEAD_WITCH_H
