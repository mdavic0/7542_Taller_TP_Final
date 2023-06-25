#ifndef LEFT4DEAD_P90PLAYER_H
#define LEFT4DEAD_P90PLAYER_H

#include "Player.h"
#include "Event.h"
#include "P90.h"
#include "Configuration.h"
#include "BlitzAtack.h"


class P90Player : public Player {
    private:
        std::shared_ptr<BlitzAtack> blitz;
        bool throwingBlitzAtack;

    public:
        P90Player(std::pair<int16_t, int16_t>& position,
                  std::shared_ptr<Collidable> collidable);
        void setSkillState(Event event) override;
        void stopSkillState(Event event) override;
        void specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                          std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                          double stepTime) override;
        bool isGrenadeAvailable() override;
        bool isSmokeAvailable() override;
        void revive() override;
        ~P90Player() override;

    private:
        void throwBlitzAtack(std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks);
};


#endif //LEFT4DEAD_P90PLAYER_H
