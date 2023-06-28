#ifndef LEFT4DEAD_WITCH_H
#define LEFT4DEAD_WITCH_H
#include <cstdint>
#include "Infected.h"
#include "Event.h"
#include "Configuration.h"
#include "TypeInfected.h"


class Witch : public Infected {
    public:
        Witch(const uint16_t& id, const std::pair<int16_t, int16_t>& position,
              std::shared_ptr<Collidable> collidable);
        void specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) override;
        ~Witch() override;

    private:
        void scream(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds);
};


#endif //LEFT4DEAD_WITCH_H
