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
        getPlayer(TypeOperator anOperator, uint8_t& playerId,
              std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
              RespawnController& controller);

    private:
        std::shared_ptr<IDFPlayer>
        createIDFPlayer(uint8_t& playerId,
                        std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                        RespawnController& RC);

        std::shared_ptr<P90Player>
        createP90Player(uint8_t& playerId,
                        std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                        RespawnController& RC);

        std::shared_ptr<SCOUTPlayer>
        createSCOUTPlayer(uint8_t& playerId,
                          std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                          RespawnController& RC);
};


#endif //LEFT4DEAD_PLAYERFACTORY_H
