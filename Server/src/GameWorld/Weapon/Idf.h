#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H
#include "Weapon.h"
#include "Configuration.h"

class Idf : public Weapon {
    public:
        Idf();
        void shoot(bool right) override;
};


#endif //LEFT4DEAD_IDF_H
