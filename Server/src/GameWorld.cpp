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
    std::map<uint8_t, std::pair<uint16_t, uint16_t>> players_position;
    for (auto player : players) {
        players_position.insert({player.first, player.second.getPosition()});
    }
    return new Snapshot(players_position);
}

