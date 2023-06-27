#ifndef LEFT4DEAD_SCOUTPLAYER_H
#define LEFT4DEAD_SCOUTPLAYER_H

#include "Player.h"
#include "Event.h"
#include "Scout.h"
#include "Configuration.h"
#include "ExplosiveGrenade.h"
#include "SmokeGrenade.h"


class SCOUTPlayer : public Player {
    private:
        std::shared_ptr<ExplosiveGrenade> grenade;
        double grenadeElapsedTime;
        bool throwingGrenade;

        std::shared_ptr<SmokeGrenade> smoke;
        double smokeElapsedTime;
        bool throwingSmoke;

    public:
        SCOUTPlayer(const std::pair<int16_t, int16_t>& position,
                             std::shared_ptr<Collidable> collidable);
        void setSkillState(const Event& event) override;
        void stopSkillState(const Event& event) override;
        void specialAtack(std::list<std::shared_ptr<Grenade>>& grenades,
                          std::list<std::shared_ptr<BlitzAtack>>& blitzAtacks,
                          const double& stepTime) override;
        bool isGrenadeAvailable() override;
        bool isSmokeAvailable() override;
        void revive() override;

        ~SCOUTPlayer() override;

    private:
        void throwGrenade(std::list<std::shared_ptr<Grenade>>& grenades,
                          const double& stepTime);
        void throwSmoke(std::list<std::shared_ptr<Grenade>>& grenades,
                        const double& stepTime);
};


#endif //LEFT4DEAD_SCOUTPLAYER_H
