#include "GameWorld.h"
#include <random>
#include <functional>
#include <iterator>
#include <utility>

GameWorld::GameWorld(const TypeGame& type, uint8_t map) :
    players_amount(INITIAL_PLAYERS_AMOUNT), players(), type(type), map(map),
    collidables(), infectedId(INITIAL_INFECTED_ID), obsacleId(INITIAL_OBSTACLE_ID),
    infectedFactory(), RC() {
    this->generateInfecteds();
    this->generateObstacles();
}


uint8_t GameWorld::addPlayer(TypeOperator op) {
    std::shared_ptr<Player> newPlayer = nullptr;
    std::pair<int16_t, int16_t> position = RC.getPlayerRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            players_amount,position,20, 20);

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
#include <iostream>
void GameWorld::simulateStep() {
    if(!ended) {
        for (auto& player : players) {
            players.at(player.first)->applyStep(this->collidables, this->infecteds);
        }

    for (auto it = infecteds.cbegin(); it != infecteds.cend(); /* no increment */){
        if (not it->second->isAlive()) {
            collidables.erase(it->first);
            infecteds.erase(it++);
        } else {
            ++it;
        }
    }
}

std::shared_ptr<Snapshot> GameWorld::getSnapshot(bool first) {
    if(!ended) {
        std::vector<StOperator> playersInfo;
        for (auto& player : players) {
            playersInfo.push_back(StOperator(player.first,
                                         player.second->getTypeOperator(),
                                         player.second->getState(),
                                         player.second->getPosition(), 
                                         player.second->getHealth(),
                                         player.second->getMunition()));
        }
        
        std::vector<EnemyDto> enemies;
        for (auto& enemy : infecteds) {
            enemies.push_back(EnemyDto(enemy.first,
                                         enemy.second->getTypeInfected(),
                                         enemy.second->getState(),
                                         enemy.second->getPosition()));
        }

        if (first){

            std::vector<ObstacleDto> obsts;
            for (auto& ob : obstacles) {
                obsts.push_back(ObstacleDto(ob.first,
                                             ob.second->getTypeObstacle(),
                                             ob.second->getPosition()));
            }
            return std::make_shared<Snapshot>(playersInfo, enemies, obsts, type, map);        
        }
        return std::make_shared<Snapshot>(playersInfo, enemies);
    }
    return std::make_shared<Snapshot>(Event::event_end);
}

std::shared_ptr<Snapshot> GameWorld::getStats() {
    return std::make_shared<Snapshot>(10000, 1000, infectedId);
}

void GameWorld::generateInfecteds() {
    switch (this->type) {
        case TypeGame::game_idle:
            break;
        case TypeGame::game_survival:
            // TODO: implement survival mode logic (ex: when all the infecteds are dead, respawn
            //  new infecteds and increment difficulty)
            this->infecteds = infectedFactory.generateInfecteds(TypeDifficulty::difficulty_easy,
                                                                infectedId,
                                                                collidables,
                                                                RC);
            break;
        case TypeGame::game_clear_zone:
            this->infecteds = infectedFactory.generateInfecteds(TypeDifficulty::difficulty_easy,
                                                                infectedId,
                                                                collidables,
                                                                RC);
            break;
        default:
            break;
    }
}

// TODO: IMPLEMENT ObstacleFactory
void GameWorld::generateObstacles() {
    // Random obstacle (can be Tire or Crater):
    std::shared_ptr<Obstacle> newObstacle = nullptr;
    std::pair<int16_t, int16_t> position = RC.getObstacleRespawnPosition();

    std::shared_ptr<Collidable> collidable =  std::make_shared<Collidable>(
            (int)obsacleId,position,50, 50);

    TypeObstacle obstacle = this->generateObstacleType();

    switch (obstacle) {
        case TypeObstacle::obstacle_tire:
            newObstacle = std::make_shared<Tire>(obsacleId, position, collidable);
            break;
        case TypeObstacle::obstacle_crater:
            newObstacle = std::make_shared<Crater>(obsacleId, position, collidable);
            break;
        default:
            newObstacle = std::make_shared<Tire>(obsacleId, position, collidable);
            break;
    }

    this->collidables.insert({obsacleId, collidable});
    this->obstacles.insert({obsacleId++, newObstacle});
}

TypeObstacle GameWorld::generateObstacleType() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<int> distr(0, 1);
    return (TypeObstacle)distr(generator);
}

bool GameWorld::isEnded() {
    return ended;
}
