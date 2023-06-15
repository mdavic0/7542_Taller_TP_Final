#include "GameSdl.h"
#include "Defines.h"
#include "Operator.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, std::map<uint8_t, std::shared_ptr<Operator>>& soldiers,
    uint8_t idPlayer, uint8_t idMap, TypeGame mode, Font& font,
    std::map<uint8_t, std::shared_ptr<Enemy>>& enemies,
    std::map<uint8_t, std::shared_ptr<Obstacles>>& obstacles) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(idMap, this->renderer, this->window), soldiers(soldiers),
    hud(soldiers[idPlayer]->getType(), mode, renderer, font, window),
    idPlayer(idPlayer), mode(mode), font(font), enemies(enemies),
    camera(window), obstacles(obstacles) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::render() {
    this->map.render(camera.getRect());
    
    for (const auto &obstacle: obstacles)
        obstacle.second->render(camera.getRect());

    this->hud.render(soldiers[idPlayer]->getHealth(), 0, enemies.size());
    std::vector<std::pair<uint8_t,std::shared_ptr<Operator>>> vec(
        soldiers.begin(), soldiers.end());
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto&b) {
        return a.second->getPosY() < b.second->getPosY();
    });
    for (const auto &soldier : vec)
        soldier.second->render(camera.getRect());
    for (const auto &enemy : enemies)
        enemy.second->render(camera.getRect());
}

void GameSdl::update() {
    camera.update(soldiers[idPlayer]->getPosition());
    std::shared_ptr<Snapshot> snap = snapshotQueue.pop();
    for (auto &player : snap->getInfo()) {
        soldiers[player.getId()]->update(player.getPosition(),
                                            player.getState(),
                                            player.getHealth());
    }

    // Si no se actualizaron todos significa que alguno se desconecto
    if (soldiers.size() > snap->getInfo().size()) {
        for (auto &player : soldiers) {
            bool found = false;
            for (const auto& stOperator : snap->getInfo())
                if (player.first == stOperator.getId()) {
                    found = true;
                    break;
                }
            if (!found)
                player.second->setState(State::dead);
        }
    }

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
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

