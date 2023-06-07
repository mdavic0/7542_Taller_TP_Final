#include "GameWorld.h"

GameWorld::GameWorld(const TypeGame& type) :
    players_amount(0), players(), type(type), map(0) {}

uint8_t GameWorld::addPlayer(TypeOperator op) {
    this->players.insert({players_amount, Player(op)});
    return players_amount++;
}

void GameWorld::deletePlayer(uint8_t id) {
    this->players.erase(id);
}

void GameWorld::updateMovementDirection(Event event, uint8_t id, MoveTo direction) {
    if (event == Event::event_move) {
        players.at(id).setMovementDirection(direction);
    } else {
        players.at(id).stopMovementDirection(direction);        
    }
}

void GameWorld::simulateStep() {
    for (auto player : players) {
        players.at(player.first).applyStep();
    }
}

std::shared_ptr<Snapshot> GameWorld::getSnapshot(bool first) {
    std::map<uint8_t, StOperator> playersInfo;
    for (auto player : players) {
        playersInfo.insert({player.first, StOperator(player.first, player.second.getTypeOperator(), player.second.getState(),
        player.second.getPosition(), player.second.getHealth())});
    }
    if (first){
        return std::make_shared<Snapshot>(playersInfo, type, map);        
    }
    return std::make_shared<Snapshot>(playersInfo);
}


