#ifndef LEFT4DEAD_IDFPLAYER_H
#define LEFT4DEAD_IDFPLAYER_H

#include "Player.h"
#include "Event.h"
#include "Idf.h"
#include "Configuration.h"
#include "ExplosiveGrenade.h"
#include "SmokeGrenade.h"


class IDFPlayer : public Player {
    private:
        std::shared_ptr<ExplosiveGrenade> grenade;
        double grenadeElapsedTime;
        bool throwingGrenade;

        std::shared_ptr<SmokeGrenade> smoke;
        double smokeElapsedTime;
        bool throwingSmoke;

    public:
        IDFPlayer(std::pair<int16_t, int16_t>& position,
                           std::shared_ptr<Collidable> collidable);
        void setSkillState(Event event) override;
        void stopSkillState(Event event) override;
        void specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                          std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                          double stepTime) override;
        bool isGrenadeAvailable() override;
        bool isSmokeAvailable() override;
        void revive() override;

        ~IDFPlayer() override;

    private:
        void throwGrenade(std::list<std::shared_ptr<Grenade>>& grenades,
                          double stepTime);
        void throwSmoke(std::list<std::shared_ptr<Grenade>>& grenades,
                        double stepTime);
};


#endif //LEFT4DEAD_IDFPLAYER_H
