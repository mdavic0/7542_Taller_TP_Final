#ifndef LEFT4DEAD_SCOUTPLAYER_H
#define LEFT4DEAD_SCOUTPLAYER_H
#include "Player.h"
#include "Event.h"
#include "Scout.h"

class SCOUTPlayer : public Player {
    public:
        SCOUTPlayer(std::pair<uint16_t, uint16_t>& position,
                             std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~SCOUTPlayer() override;
    private:
        void throwGrenade();
        void throwSmoke();
};


#endif //LEFT4DEAD_SCOUTPLAYER_H
