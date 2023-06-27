#include "GameWorld.h"
#include <random>
#include <functional>
#include <iterator>
#include <utility>
#include <algorithm>
#include <iostream>


GameWorld::GameWorld(const TypeGame& type, const TypeDifficulty& difficulty) :
    players_amount(INITIAL_PLAYERS_AMOUNT), players(), type(type), map(this->generateMapType()),
    collidables(), infectedId(INITIAL_INFECTED_ID), obsacleId(INITIAL_OBSTACLE_ID),
    infectedFactory(), RC(), ended(false), obstacleFactory(), playerFactory(),
    deadPlayersId(), difficulty(difficulty), rounds(0), mapLimitId(INITIAL_MAP_LIMIT_ID) {
    this->generateInfecteds();
    this->generateObstacles();
    this->generateMapLimits();
}

uint16_t GameWorld::addPlayer(const TypeOperator& op) {
    std::shared_ptr<Player> newPlayer = playerFactory.getPlayer(op,
                                                                players_amount,
                                                                collidables,
                                                                RC);
    this->players.insert({players_amount, newPlayer});
    return players_amount++;
}

void GameWorld::deletePlayer(const uint16_t& id) {
    this->players.erase(id);
    this->collidables.erase(id);
    this->deadPlayersId.push_back(id);
}

void GameWorld::updateMovementDirection(const Event& event, const uint16_t& id, const MoveTo& direction) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_move) {
        players.at(id)->setMovementDirection(direction);
    } else {
        players.at(id)->stopMovementDirection(direction);
    }
}

void GameWorld::updateShootingState(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_shoot) {
        players.at(id)->setShootingState();
    } else {
        players.at(id)->stopShootingState();
    }
}

void GameWorld::updateReloadingState(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_recharge) {
        players.at(id)->setReloadingState();
    }
}

void GameWorld::updateSkillState(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    if (found) {
        return;
    }

    if (event == Event::event_throw_grenade or
        event == Event::event_throw_smoke or
        event == Event::event_blitz_atack) {
        players.at(id)->setSkillState(event);
    } else {
        players.at(id)->stopSkillState(event);
    }
}

void GameWorld::simulateStep(const double& stepTime) {
    if(!ended) {
        simulatePlayersStep(stepTime);
        if(infecteds.empty()) {
            switch (this->type) {
                case TypeGame::game_survival:
                    updateRounds();
                    this->infecteds = infectedFactory.generateInfecteds(difficulty,
                                                                        infectedId,
                                                                        collidables,
                                                                        RC);
                    break;
                case TypeGame::game_clear_zone:
                    this->ended = true;
                    break;
                default:
                    break;
            }
        }
        simulateInfectedStep(stepTime);
        if (allPlayersAreDead()) {
            ended = true;
        } 
        simulateGrenadeStep(stepTime);
        simulateBlitzAtackStep(stepTime);
        simulatePostExplosionGrenadesStep(stepTime);
        simulateBlitzAtackStep(stepTime);
        simulatePostExplosionBlitz(stepTime);
    }
}

std::shared_ptr<Snapshot> GameWorld::getSnapshot(const bool& first) {
    if(!ended) {
        std::vector<StOperator> playersInfo;
        for (auto& player : players) {
            playersInfo.push_back(StOperator(player.first,
                                         player.second->getTypeOperator(),
                                         player.second->getState(),
                                         player.second->getPosition(), 
                                         player.second->getHealth(),
                                         player.second->getMunition(),
                                         player.second->isGrenadeAvailable(),
                                         player.second->isSmokeAvailable()));
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

        std::vector<GrenadeDto> grenadesInfo;
        for (auto& grenade : grenades) {
            grenadesInfo.push_back(GrenadeDto(grenade->exploded(),
                                         grenade->getTypeGrenade(),
                                         grenade->getPosition()));
        }
        
        bool blitzAttacking = !blitzAtacks.empty();
        
        return std::make_shared<Snapshot>(playersInfo, enemies, grenadesInfo, blitzAttacking);
    }
    return std::make_shared<Snapshot>(Event::event_end);
}

std::vector<StatsDto> GameWorld::getStats() {
    std::vector<StatsDto> stats;
    if (type == TypeGame::game_survival) {
        for (auto& player : players) {
            stats.push_back(StatsDto(player.first,
                                 player.second->getKills(),
                                 player.second->getShots()));
        }
    }
    return stats;
}

void GameWorld::generateInfecteds() {
    switch (this->type) {
        case TypeGame::game_idle:
            break;
        case TypeGame::game_survival:
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

void GameWorld::generateObstacles() {
    // Random obstacles (can be Tire or Crater):
    for (int i = 0; i < CF::obstacle_amount; i++) {
        std::shared_ptr<Obstacle> newObstacle = this->obstacleFactory.getObstacle(generateObstacleType(),
                                                                                  obsacleId,
                                                                                  collidables,
                                                                                  RC);
        this->obstacles.insert({obsacleId++, newObstacle});
    }
}

void GameWorld::generateMapLimits() {
    // LEFT LIMIT
    std::pair<int16_t, int16_t> leftLimitpos = {0, MAP_HEIGTH * 0.8};

    std::shared_ptr<Collidable> leftMapLimit =  std::make_shared<Collidable>(
            mapLimitId, leftLimitpos, 100, MAP_HEIGTH);

    this->collidables.insert({mapLimitId++, leftMapLimit});

    // RIGHT LIMIT
    std::pair<int16_t, int16_t> rightLimitpos = {MAP_WIDTH, MAP_HEIGTH * 0.8};
    std::shared_ptr<Collidable> rightMapLimit =  std::make_shared<Collidable>(
            mapLimitId, rightLimitpos, 100, MAP_HEIGTH);

    this->collidables.insert({mapLimitId++, rightMapLimit});

    // UPPER LIMIT
    std::pair<int16_t, int16_t> upperLimitpos = {MAP_WIDTH / 2.0, MAP_HEIGTH * 0.75};
    std::shared_ptr<Collidable> upperMapLimit =  std::make_shared<Collidable>(
            mapLimitId, upperLimitpos, MAP_WIDTH, 10);

    this->collidables.insert({mapLimitId++, upperMapLimit});

    // DOWN LIMIT
    std::pair<int16_t, int16_t> downLimitpos = {MAP_WIDTH / 2.0, MAP_HEIGTH * 0.92};

    std::shared_ptr<Collidable> downMapLimit =  std::make_shared<Collidable>(
            mapLimitId, downLimitpos, MAP_WIDTH, 10);

    this->collidables.insert({mapLimitId++, downMapLimit});
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

int GameWorld::generateMapType() {
    std::random_device rand_dev;
    std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<short> distr(1, 3);
    return distr(generator);
}

void GameWorld::simulatePlayersStep(const double& stepTime) {
    // Erase dead players
    for (auto it = players.cbegin(); it != players.cend(); /*no increment*/ ){
        if (not it->second->isAlive()) {
            deadPlayersId.push_back(it->first);
            collidables.erase(it->first);
            //players.erase(
                it++;//);
        } else {
            ++it;
        }
    }

    // Apply players step
    for (auto& player : players) {
        players.at(player.first)->applyStep(this->collidables,
                                            this->infecteds,
                                            this->grenades,
                                            this->blitzAtacks,
                                            stepTime);
    }
}

void GameWorld::simulateInfectedStep(const double& stepTime) {
    if (not ended) {
        // Erase dead infecteds
        for (auto it = infecteds.cbegin(); it != infecteds.cend(); /* no increment */){
            if (not it->second->isAlive()) {
                collidables.erase(it->first);
                infecteds.erase(it++);
            } else {
                ++it;
            }
        }

        // Apply infecteds step
        for (auto& infected : infecteds) {
            infecteds.at(infected.first)->applyStep(this->collidables, this->players);
        }
    }
}

void GameWorld::simulateGrenadeStep(const double& stepTime) {
    if (not ended) {
        // Erase exploded grenades
        for (auto it = grenades.cbegin(); it != grenades.cend(); /* no increment */){
            if ((*it)->exploded()) {
                // Post explosion the grenades still need to simulate steps
                // till it is available again (while reloading)
                postExplosionGrenades.push_back((*it));
                grenades.erase(it++);
            } else {
                ++it;
            }
        }

        // Apply grenade step
        for (auto& grenade : grenades) {
            grenade->applyStep(this->players, this->infecteds, stepTime);
        }
    }
}

void GameWorld::simulateBlitzAtackStep(const double& stepTime) {
    if (not ended) {
        // Erase ended blitz atack
        for (auto it = blitzAtacks.cbegin(); it != blitzAtacks.cend(); /* no increment */){
            if ((*it)->ended()) {
                // Post explosion the blitz atacks still need to simulate steps
                // till it is available again (while reloading)
                postExplosionBlitz.push_back((*it));
                blitzAtacks.erase(it++);
            } else {
                ++it;
            }
        }

        // Apply blitz step
        for (auto& blitzAtack : blitzAtacks) {
            blitzAtack->applyStep(this->infecteds, stepTime);
        }
    }
}

void GameWorld::simulatePostExplosionGrenadesStep(const double& stepTime) {
    if (not ended) {
        // Erase availables grenades
        for (auto it = postExplosionGrenades.cbegin(); it != postExplosionGrenades.cend(); /* no increment */){
            if ((*it)->isAvailable()) {
                postExplosionGrenades.erase(it++);
            } else {
                ++it;
            }
        }

        // Apply postExplosionGrenade step
        for (auto& grenade : postExplosionGrenades) {
            grenade->applyStep(this->players, this->infecteds, stepTime);
        }
    }
}

bool GameWorld::allPlayersAreDead() {
    if (deadPlayersId.empty())
        return false;

    for (const auto& id : deadPlayersId) {
        if (players.find(id) == players.end()) {
            return false;
        }
    }
    return true;
}

void GameWorld::simulatePostExplosionBlitz(const double& stepTime) {
    if (not ended) {
        // Erase availables blitz
        for (auto it = postExplosionBlitz.cbegin(); it != postExplosionBlitz.cend(); /* no increment */){
            if ((*it)->isAvailable()) {
                postExplosionBlitz.erase(it++);
            } else {
                ++it;
            }
        }

        // Apply postExplosionBlitz step
        for (auto& blitz : postExplosionBlitz) {
            blitz->applyStep(this->infecteds, stepTime);
        }
    }
}

void GameWorld::updateRounds() {
    RC.resetRespawns(); // to ensure that there are available respawn positions
    rounds++;
    if (rounds < 21 && rounds % 5 == 0) {
        switch (difficulty) {
        case TypeDifficulty::difficulty_easy:
            difficulty = TypeDifficulty::difficulty_normal;
                break;
        case TypeDifficulty::difficulty_normal:
            difficulty = TypeDifficulty::difficulty_hard;
                break;
        case TypeDifficulty::difficulty_hard:
            difficulty = TypeDifficulty::difficulty_god;
                break;
        default:
            difficulty = TypeDifficulty::difficulty_god;
                break;
        }
    }

}

void GameWorld::reanimatePlayer(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_reanimate) {
        players.at(id)->reanimate(this->players);
    }
}

void GameWorld::finishGame(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_cheat_finish_game) {
        this->ended = true;
    }
}

void GameWorld::applySuperSpeed(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_cheat_more_velocity) {
        players.at(id)->applySpeed(CF::super_speed_increment);
    }
}

void GameWorld::killInfecteds(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_cheat_kill_enemies) {
        for (auto it = infecteds.cbegin(); it != infecteds.cend(); /* no increment */){
                collidables.erase(it->first);
                infecteds.erase(it++);
        }
    }
}

void GameWorld::makeInmortal(const Event& event, const uint16_t& id) {
    bool found = (std::find(deadPlayersId.begin(),
                            deadPlayersId.end(),
                            id) != deadPlayersId.end());
    // Ignore actions from dead players
    if (found) {
        return;
    }

    if (event == Event::event_cheat_infinite_health) {
        players.at(id)->makeImmortal();
    }
}

