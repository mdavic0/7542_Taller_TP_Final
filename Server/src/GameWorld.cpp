#include "GameWorld.h"

GameWorld::GameWorld() : players_amount(0), players() {}

void GameWorld::add_player(TypeOperator id) {
    this->players.insert({id, Player(id)});
}

void GameWorld::delete_player(TypeOperator id) {
    this->players.erase(id);
}

void GameWorld::update_movement_direction(TypeOperator id, MoveTo direction) {
    players.at(id).set_movement_direction(direction);
}

void GameWorld::simulate_step() {
 for(int i = 0; i < players_amount; i++) {
     players.at((TypeOperator)i).apply_step();
 }
}

Snapshot *GameWorld::get_snapshot() {
    return new Snapshot(this->players);
}
