#ifndef LEFT4DEAD_VENOM_H
#define LEFT4DEAD_VENOM_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"
#include "TypeInfected.h"

class Venom : public Infected {
    public:
        Venom(const uint8_t& id, const std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;
        ~Venom() override;

    private:
        void throwVenom();
};


#endif //LEFT4DEAD_VENOM_H
