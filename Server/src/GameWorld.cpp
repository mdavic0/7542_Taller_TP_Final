#include "GameWorld.h"

GameWorld::GameWorld() : players_amount(0), players() {}

void GameWorld::addPlayer(TypeOperator id) {
    this->players.insert({id, Player(id)});
    players_amount++;
}

void GameWorld::deletePlayer(TypeOperator id) {
    this->players.erase(id);
}

#include <iostream>
void GameWorld::updateMovementDirection(Event event, TypeOperator id, MoveTo direction) {
    std::cout << "Actualizando direccion de movimiento\n";
    if (event == Event::event_move) {
        std::cout << "El evento es move\n";
        players.at((TypeOperator)1).setMovementDirection(direction);
    } else {
        std::cout << "El evento es stop move\n";
        players.at(id).stopMovementDirection(direction);        
    }
    std::cout << "Direccion de movimiento actualizada\n";
}

void GameWorld::simulateStep() {
    for (auto player : players) {
        players.at(player.first).applyStep();
    }
}

Snapshot *GameWorld::getSnapshot() {
    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> players_position;
    for (auto player : players) {
        players_position.insert({player.first, player.second.getPosition()});
    }
    return new Snapshot(players_position);
}

