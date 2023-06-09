#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H
#include "Weapon.h"
#include "Configuration.h"
#include "Collidable.h"
#include "Infected.h"

class Idf : public Weapon {
    public:
        Idf();
        void shoot(std::shared_ptr<Collidable>& player, bool right,
                   std::map<uint8_t, std::shared_ptr<Infected>>& infecteds) override;
};


#endif //LEFT4DEAD_IDF_H
