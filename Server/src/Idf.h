#ifndef LEFT4DEAD_IDF_H
#define LEFT4DEAD_IDF_H
#include "Weapon.h"

class Idf : public Weapon {
    public:
        Idf();
        void shoot(Event event) override;
};


#endif //LEFT4DEAD_IDF_H
