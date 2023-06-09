#ifndef LEFT4DEAD_IDFPLAYER_H
#define LEFT4DEAD_IDFPLAYER_H
#include "Player.h"
#include "Event.h"
#include "Idf.h"

class IDFPlayer : public Player {
    public:
        IDFPlayer(std::pair<int16_t, int16_t>& position,
                           std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~IDFPlayer() override;
    private:
        void throwGrenade();
        void throwSmoke();
};


#endif //LEFT4DEAD_IDFPLAYER_H
