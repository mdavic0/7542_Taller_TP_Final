#include "GameWorld.h"

GameWorld::GameWorld() : players_amount(0), players() {}

void GameWorld::addPlayer(TypeOperator id) {
    this->players.insert({id, Player(id)});
    players_amount++;
}

void GameWorld::deletePlayer(TypeOperator id) {
    this->players.erase(id);
}

void GameWorld::updateMovementDirection(TypeOperator id, MoveTo direction) {
    players.at(id).set_movement_direction(direction);
}

void GameWorld::simulateStep() {
    for (auto player : players) {
        players.at(player.first).apply_step();
    }
}

Snapshot *GameWorld::getSnapshot() {
    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> players_position;
    for (auto player : players) {
        players_position.insert({player.first, player.second.get_position()});
    }
    return new Snapshot(players_position);
}

