#include "GameWorld.h"

GameWorld::GameWorld(const TypeGame& type) :
    players_amount(0), players(), type(type), map(0), collidables() {}


uint8_t GameWorld::addPlayer(TypeOperator op) {
    std::shared_ptr<Player> newPlayer = nullptr;
    std::pair<uint16_t, uint16_t> position = {(WINDOW_WIDTH / 2) + 40 * players_amount,
                                              (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 4)};

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            (int)players_amount,position,20, 20);

    switch (op) {
        case TypeOperator::operator_idf:
            newPlayer = std::make_shared<IDFPlayer>(position, collidable);
            break;
        case TypeOperator::operator_scout:
            newPlayer = std::make_shared<SCOUTPlayer>(position, collidable);
            break;
        case TypeOperator::operator_p90:
            newPlayer = std::make_shared<P90Player>(position, collidable);
            break;
        default:
            newPlayer = std::make_shared<IDFPlayer>(position, collidable);
            break;
    }
    this->collidables.insert({players_amount, collidable});
    this->players.insert({players_amount, newPlayer});
    return players_amount++;
}

void GameWorld::deletePlayer(uint8_t id) {
    this->players.erase(id);
}

void GameWorld::updateMovementDirection(Event event, uint8_t id, MoveTo direction) {
    if (event == Event::event_move) {
        players.at(id)->setMovementDirection(direction);
    } else {
        players.at(id)->stopMovementDirection(direction);
    }
}

void GameWorld::updateShootingState(Event event, uint8_t id) {
    if (event == Event::event_shoot) {
        players.at(id)->setShootingState();
    } else {
        players.at(id)->stopShootingState();
    }
}

void GameWorld::simulateStep() {
    for (auto& player : players) {
        players.at(player.first)->applyStep(this->collidables);
    }
}

std::shared_ptr<Snapshot> GameWorld::getSnapshot(bool first) {
    std::map<uint8_t, StOperator> playersInfo;
    for (auto& player : players) {
        playersInfo.insert({player.first, StOperator(player.first,
                                                     player.second->getTypeOperator(),
                                                     player.second->getState(),
        player.second->getPosition(), player.second->getHealth())});
    }
    if (first){
        return std::make_shared<Snapshot>(playersInfo, type, map);        
    }
    return std::make_shared<Snapshot>(playersInfo);
}
