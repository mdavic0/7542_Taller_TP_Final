#ifndef LEFT4DEAD_IDFPLAYER_H
#define LEFT4DEAD_IDFPLAYER_H
#include "Player.h"
#include "Event.h"
#include "Idf.h"

class IDFPlayer : public Player {
    public:
        IDFPlayer();
        void specialAtack(Event event) override;
        ~IDFPlayer() override;
    private:
        void throwGrenade();
        void throwSmoke();
};


#endif //LEFT4DEAD_IDFPLAYER_H
