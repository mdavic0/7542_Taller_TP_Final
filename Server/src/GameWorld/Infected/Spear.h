#ifndef LEFT4DEAD_SPEAR_H
#define LEFT4DEAD_SPEAR_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"
#include "TypeInfected.h"

class Spear : public Infected {
    public:
        Spear(const uint16_t id, const std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(const Event& event) override;
        ~Spear() override;

    private:
        void throwSpear();
};


#endif //LEFT4DEAD_SPEAR_H
