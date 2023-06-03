#include "GameWorld.h"

GameWorld::GameWorld() : players_amount(0), players() {}

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

Snapshot *GameWorld::getSnapshot() {
    std::map<uint8_t, StOperator> playersInfo;
    for (auto player : players) {
        playersInfo.insert({player.first, StOperator(player.first, player.second.getTypeOperator(), player.second.getState(),
        player.second.getPosition(), player.second.getHealth())});
    }
    return new Snapshot(playersInfo);
}


