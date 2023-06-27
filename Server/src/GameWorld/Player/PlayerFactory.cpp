#include "PlayerFactory.h"
#include "Defines.h"

std::shared_ptr<Player> PlayerFactory::getPlayer(const TypeOperator& anOperator, const uint16_t &playerId,
                                                 std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                                 RespawnController &controller) {
    switch (anOperator) {
        case TypeOperator::operator_p90:
            return createP90Player(playerId,
                                   collidables,
                                   controller);
        case TypeOperator::operator_idf:
            return createIDFPlayer(playerId,
                                   collidables,
                                   controller);
        case TypeOperator::operator_scout:
            return createSCOUTPlayer(playerId,
                                     collidables,
                                     controller);
        default:
            return createP90Player(playerId,
                                   collidables,
                                   controller);
    }
}

std::shared_ptr<IDFPlayer>
PlayerFactory::createIDFPlayer(const uint16_t &playerId,
                               std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                               RespawnController& RC) {
    std::pair<int16_t, int16_t> position = RC.getPlayerRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            playerId,position,PLAYER_WIDTH, PLAYER_HEIGHT);

    collidables.insert({playerId, collidable});

    return std::make_shared<IDFPlayer>(position, collidable);
}

std::shared_ptr<P90Player>
PlayerFactory::createP90Player(const uint16_t &playerId, std::map<uint16_t,
                               std::shared_ptr<Collidable>> &collidables,
                               RespawnController& RC) {
    std::pair<int16_t, int16_t> position = RC.getPlayerRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            playerId,position,PLAYER_WIDTH, PLAYER_HEIGHT);

    collidables.insert({playerId, collidable});

    return std::make_shared<P90Player>(position, collidable);
}

std::shared_ptr<SCOUTPlayer>
PlayerFactory::createSCOUTPlayer(const uint16_t &playerId, std::map<uint16_t,
                                 std::shared_ptr<Collidable>> &collidables,
                                 RespawnController& RC) {
    std::pair<int16_t, int16_t> position = RC.getPlayerRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            playerId,position,PLAYER_WIDTH, PLAYER_HEIGHT);

    collidables.insert({playerId, collidable});

    return std::make_shared<SCOUTPlayer>(position, collidable);
}
