#include "GameSdl.h"
#include "Defines.h"
#include "Operator.h"
#include "Object.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, uint8_t idPlayer, Font& font, ConfigGame& config) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(config.getTextureManager(), renderer, window),
    soldiers(config.getPlayers()),
    hud(soldiers[idPlayer]->getType(), config.getMode(), renderer, font, window),
    idPlayer(idPlayer), mode(config.getMode()), font(font),
    enemies(config.getEnemies()), camera(window), obstacles(config.getObstacles()) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::render() {
    this->map.render(camera.getRect());
    // std::cout << "mapRender\n";

    this->hud.render(soldiers[idPlayer]->getHealth(),
                    soldiers[idPlayer]->getMunition(),
                    enemies.size());
    // std::cout << "hudRender\n";
    
    // reordeno todo antes de renderizar
    std::vector<std::shared_ptr<Object>> vecObjects;
    for (const auto &obstacle: obstacles)
        vecObjects.push_back(obstacle.second);
    for (const auto &enemy : enemies)
        vecObjects.push_back(enemy.second);
    for (const auto &soldier : soldiers)
        vecObjects.push_back(soldier.second);
        
    std::sort(vecObjects.begin(), vecObjects.end(),
        [](const auto& a, const auto&b) {
            return a->getPosY() <= b->getPosY();
    });
    for (const auto &object : vecObjects)
        object->render(camera.getRect());
    // std::cout << "restoRender\n";
}

void GameSdl::update() {
    std::shared_ptr<Snapshot> snap = nullptr;
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
            // std::cout << "soldiersUpdate\n";
        }

        camera.update(calculateMassCenter());

        // if (enemies.size() >= snap->getEnemies().size()) {
        //     for (auto &enemy : enemies) {
        //         bool found = false;
        //         for (const auto& enemyDto : snap->getEnemies())
        //             if (enemy.first == enemyDto.getId()) {
        //                 enemy.second->update(enemyDto.getPosition(),
        //                                     enemyDto.getState());
        //                 found = true;
        //                 break;
        //             }
        //         if (!found)
        //             enemies.erase(enemy.first);
        //     }
        //     // std::cout << "enemiesUpdate\n";
        // }
        std::unordered_set<uint8_t> mapIds;
        for (auto &infected : snap->getEnemies()) {
            mapIds.insert(infected.getId());
            enemies[infected.getId()]->update(infected.getPosition(),
                                                infected.getState());
        }

        // Eliminio enemigo muerto
        auto iterator = enemies.begin();
        while (iterator != enemies.end()) {
            if (mapIds.find(iterator->first) == mapIds.end())
                iterator = enemies.erase(iterator);
            else
                ++iterator;
        }
    } else {
        this->endGame = true;
    }
}

std::pair<int16_t, int16_t> GameSdl::calculateMassCenter() {
    std::pair<int16_t, int16_t> massCenter;
    size_t soldiersLive = 0;
    for (const auto& soldier : soldiers) {
        if (soldier.second->getState() != State::dead) {
            massCenter.first += soldier.second->getPosX();
            massCenter.second += soldier.second->getPosY();
            soldiersLive++;
        }
    }
    massCenter.first = massCenter.first / soldiersLive;
    massCenter.second = massCenter.second / soldiersLive;
    return massCenter;
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

