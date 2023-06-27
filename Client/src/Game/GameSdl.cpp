#include "GameSdl.h"
#include "Defines.h"
#include "Operator.h"
#include "Object.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include "BlitzSdl.h"

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    uint8_t idPlayer, Font& font, ConfigGame& config) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(false), events(eventQueue, idPlayer, endGame),
    map(config.getTextureManager(), renderer, window),
    soldiers(config.getPlayers()),
    hud(soldiers[idPlayer]->getType(), config.getMode(), renderer, font,
    window), idPlayer(idPlayer), mode(config.getMode()), font(font),
    enemies(config.getEnemies()), camera(window),
    obstacles(config.getObstacles()), grenades(),
    textures(config.getTextureManager()), music(config.getManagerMusic()),
    blitzAttack(false), endGameSdl(font, renderer, config.getTextureManager(),
    config.getMode(), window) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::render() {
    this->map.render(camera.getRect());
   
    this->hud.render(soldiers[idPlayer]->getHealth(),
                    soldiers[idPlayer]->getMunition(),
                    endGame ? 0 : enemies.size(),
                    soldiers[idPlayer]->getGrenadeAvailable(),
                    soldiers[idPlayer]->getSmokeAvailable());
    
    // reordeno todo antes de renderizar
    std::vector<std::shared_ptr<Object>> vecObjects;
    for (const auto &obstacle: obstacles)
        vecObjects.push_back(obstacle.second);
    for (const auto &enemy : enemies) {
        if (endGame) {
            if (mode == TypeGame::game_clear_zone)
                enemy.second->setState(State::dead);
            else if (mode == TypeGame::game_survival)
                enemy.second->setState(State::idle);
        }
        vecObjects.push_back(enemy.second);
    }
    for (const auto &soldier : soldiers) {
        if (endGame) {
            if (mode == TypeGame::game_clear_zone)
                soldier.second->setState(State::idle);
            else if (mode == TypeGame::game_survival)
                soldier.second->setState(State::dead);
        }
        vecObjects.push_back(soldier.second);
    }
        
    std::sort(vecObjects.begin(), vecObjects.end(),
        [](const auto& a, const auto&b) {
            return a->getPosY() <= b->getPosY();
    });
    for (const auto &object : vecObjects)
        object->render(camera.getRect());

    for (const auto &grenade : grenades)
        grenade->render(camera.getRect());
    this->renderBlitz();

    if (endGame) {
        endGameSdl.render();
        music.stopEffects();
    }
}

void GameSdl::renderBlitz() {
    if (this->blitzAttack) {
        BlitzSdl blitz(renderer, textures, music, window);
        blitz.render(camera.getRect());
        this->blitzAttack = false;
    }
}

void GameSdl::update() {
    std::shared_ptr<Snapshot> snap = nullptr;
    if (!endGame) {
        while (!snapshotQueue.try_pop(snap)) {
        }
        if (snap->getEvent() != Event::event_end) {
            if (soldiers.size() >= snap->getInfo().size()) {
                for (auto &player : soldiers) {
                    bool found = false;
                    for (const auto& stOperator : snap->getInfo())
                        if (player.first == stOperator.getId()) {
                            player.second->update(stOperator);
                            found = true;
                            break;
                        }
                    if (!found)
                        player.second->setState(State::dead);
                }
            }
            
            camera.update(calculateMassCenter());

            std::unordered_set<uint8_t> mapIds;
            for (auto &infected : snap->getEnemies()) {
                mapIds.insert(infected.getId());
                enemies[infected.getId()]->update(infected.getPosition(),
                                                    infected.getState());
            }

            // Eliminio enemigo muerto
            auto iterator = enemies.begin();
            while (iterator != enemies.end()) {
                if (mapIds.find(iterator->first) == mapIds.end()) {
                    if (iterator->second->isDeadFinish()) {
                        iterator = enemies.erase(iterator);
                    } else {
                        iterator->second->setState(State::dead);
                        if (mode == TypeGame::game_clear_zone)
                        ++iterator;
                    }
                } else {
                    ++iterator;
                }
            }
            this->updateGrenades(snap);
            this->blitzAttack = snap->getBlitzAttacking(); 
        } else {
            this->endGame = true;
            if (mode == TypeGame::game_survival) {
                snap = snapshotQueue.pop();
                if (snap->getEvent() == Event::event_stats) {
                    std::cout << "llego stats\n";
                    endGameSdl.addStats(snap->getStats());
                }
            }
        }
    }
}

void GameSdl::updateGrenades(std::shared_ptr<Snapshot> snap) {
    if (grenades.empty()) {
        for (const auto &grenade : snap->getGrenades()) {
            grenades.push_back(
                std::make_shared<GrenadeSdl>(grenade, textures, renderer,
                                            music));
        }
    } else {
        std::list<std::shared_ptr<GrenadeSdl>> updatedGrenades;
        for (const auto& grenade : grenades) {
            if (!grenade->exploded())
                updatedGrenades.push_back(grenade);
        }

        const auto& newGrenades = snap->getGrenades();
        for (const auto& grenade : newGrenades) {
            bool exists = false;
            for (const auto& updatedGrenade : updatedGrenades) {
                if (updatedGrenade->getType() == grenade.getTypeGrenade()) {
                    exists = true;
                    updatedGrenade->update(grenade);
                    break;
                }
            }
            if (!exists) {
                updatedGrenades.push_back(
                    std::make_shared<GrenadeSdl>(grenade, textures, renderer,
                                                music));
            }
        }
        grenades = std::move(updatedGrenades);
    }
}

std::pair<int16_t, int16_t> GameSdl::calculateMassCenter() {
    std::pair<int16_t, int16_t> massCenter = {0, 0};
    size_t soldiersLive = 0;
    for (const auto& soldier : soldiers) {
        if (soldier.second->getState() != State::dead) {
            massCenter.first += soldier.second->getPosX();
            massCenter.second += soldier.second->getPosY();
            soldiersLive++;
        }
    }
    if (soldiersLive != 0) {
        massCenter.first = massCenter.first / soldiersLive;
        massCenter.second = massCenter.second / soldiersLive;
    } else {
        massCenter.first = soldiers[idPlayer]->getPosX();
        massCenter.second = soldiers[idPlayer]->getPosY();
    }
    return massCenter;
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

