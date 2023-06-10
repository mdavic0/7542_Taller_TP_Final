#include "GameWorld.h"

GameWorld::GameWorld(const TypeGame& type, int map) :
    players_amount(0), players(), type(type), map(map), collidables(), infectedId(200) {
    this->generateInfecteds();
}


uint8_t GameWorld::addPlayer(TypeOperator op) {
    std::shared_ptr<Player> newPlayer = nullptr;
    std::pair<int16_t, int16_t> position = {(WINDOW_WIDTH / 2) + SIZE_SPRITE_X * players_amount,
                                              (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5)};

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
    this->collidables.erase(id);
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
        players.at(player.first)->applyStep(this->collidables, this->infecteds);
    }

    for(auto& infected : infecteds) {
        if (not infected.second->isAlive()) {
            this->infecteds.erase(infected.first);
            this->collidables.erase(infected.first);
        }
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

void GameWorld::generateInfecteds() {
    // Zombie:
    std::shared_ptr<Infected> zombie = nullptr;
    std::pair<int16_t, int16_t> zombie_position = {(WINDOW_WIDTH / 2) - 50,
                                                   (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) - 25};
    std::shared_ptr<Collidable> zombie_collidable =  std::make_shared<Collidable>(
            (int)players_amount, zombie_position, 20,  20);
    zombie = std::make_shared<Zombie>(infectedId, zombie_position, zombie_collidable);
    this->collidables.insert({infectedId, zombie_collidable});
    this->infecteds.insert({infectedId++, zombie});

    // Spear:
    std::shared_ptr<Infected> spear = nullptr;
    std::pair<int16_t, int16_t> spear_position = {(WINDOW_WIDTH / 2) - 50,
                                                  (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5)};
    std::shared_ptr<Collidable> spear_collidable =  std::make_shared<Collidable>(
            (int)players_amount, spear_position, 20,  20);
    spear = std::make_shared<Spear>(infectedId, spear_position, spear_collidable);
    this->collidables.insert({infectedId, spear_collidable});
    this->infecteds.insert({infectedId++, spear});

    // Venom:
    std::shared_ptr<Infected> venom = nullptr;
    std::pair<int16_t, int16_t> venom_position = {(WINDOW_WIDTH / 2) - 50,
                                                  (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 25};
    std::shared_ptr<Collidable> venom_collidable =  std::make_shared<Collidable>(
            (int)players_amount,venom_position,20, 20);
    venom = std::make_shared<Venom>(infectedId, venom_position, venom_collidable);
    this->collidables.insert({infectedId, venom_collidable});
    this->infecteds.insert({infectedId++, venom});

    // Jumper:
    std::shared_ptr<Infected> jumper = nullptr;
    std::pair<int16_t, int16_t> jumper_position = {(WINDOW_WIDTH / 2) - 50,
                                                   (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 50};
    std::shared_ptr<Collidable> jumper_collidable =  std::make_shared<Collidable>(
            (int)players_amount,venom_position,20, 20);
    jumper = std::make_shared<Jumper>(infectedId, jumper_position, jumper_collidable);
    this->collidables.insert({infectedId, jumper_collidable});
    this->infecteds.insert({infectedId++, jumper});

    // Witch
    std::shared_ptr<Infected> witch = nullptr;
    std::pair<int16_t, int16_t> witch_position = {(WINDOW_WIDTH / 2) - 50,
                                                   (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 75};
    std::shared_ptr<Collidable> witch_collidable =  std::make_shared<Collidable>(
            (int)players_amount,witch_position,20, 20);
    witch = std::make_shared<Witch>(infectedId, witch_position, witch_collidable);
    this->collidables.insert({infectedId, witch_collidable});
    this->infecteds.insert({infectedId++, witch});
}
