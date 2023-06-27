#ifndef LEFT4DEAD_PLAYERFACTORY_H
#define LEFT4DEAD_PLAYERFACTORY_H

#include "Player.h"
#include "P90Player.h"
#include "SCOUTPlayer.h"
#include "IDFPlayer.h"
#include "RespawnController.h"


class PlayerFactory {
    public:
        std::shared_ptr<Player>
        getPlayer(const TypeOperator& anOperator, const uint16_t& playerId,
              std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
              RespawnController& controller);

    private:
        std::shared_ptr<IDFPlayer>
        createIDFPlayer(const uint16_t& playerId,
                        std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                        RespawnController& RC);

        std::shared_ptr<P90Player>
        createP90Player(const uint16_t& playerId,
                        std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                        RespawnController& RC);

        std::shared_ptr<SCOUTPlayer>
        createSCOUTPlayer(const uint16_t& playerId,
                          std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                          RespawnController& RC);
};


#endif //LEFT4DEAD_PLAYERFACTORY_H
