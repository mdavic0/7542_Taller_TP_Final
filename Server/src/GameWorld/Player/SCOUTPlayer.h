#ifndef LEFT4DEAD_SCOUTPLAYER_H
#define LEFT4DEAD_SCOUTPLAYER_H
#include "Player.h"
#include "Event.h"
#include "Scout.h"
#include "Configuration.h"

class SCOUTPlayer : public Player {
    public:
        SCOUTPlayer(std::pair<int16_t, int16_t>& position,
                             std::shared_ptr<Collidable> collidable);
        void specialAtack(Event event) override;
        ~SCOUTPlayer() override;

    private:
        void throwGrenade();
        void throwSmoke();
};


#endif //LEFT4DEAD_SCOUTPLAYER_H
