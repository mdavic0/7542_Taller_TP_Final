#ifndef LEFT4DEAD_VENOM_H
#define LEFT4DEAD_VENOM_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"


class Venom : public Infected {
    public:
        Venom(uint8_t id, std::pair<int16_t, int16_t>& position,
            std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~Venom() override;

    private:
        void throwVenom();
};


#endif //LEFT4DEAD_VENOM_H
