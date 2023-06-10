#include "GameSdl.h"
#include "Defines.h"
#include <iostream>
#include <vector>
#include <algorithm>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, std::map<uint8_t, std::shared_ptr<Operator>>& soldiers,
    uint8_t idPlayer, uint8_t idMap, TypeGame mode, Font& font,
    std::map<uint8_t, std::shared_ptr<Enemy>>& enemies) :
    window(window), renderer(renderer), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), endGame(endGame), events(eventQueue, idPlayer),
    map(idMap, this->renderer), soldiers(soldiers),
    hud(soldiers[idPlayer]->getType(), renderer, font),
    idPlayer(idPlayer), mode(mode), font(font), enemies(enemies) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

/*
Para renderizar correctamente lo player se necesita ordenar por la posicion y
*/ 
bool comparePosition(const std::pair<uint8_t, std::shared_ptr<Operator>>& a,
                    const std::pair<uint8_t, std::shared_ptr<Operator>>& b) {
    return a.second->getPosY() < b.second->getPosY();
}

void GameSdl::render() {
    this->map.render();
    this->hud.render(soldiers[idPlayer]->getHealth(), 0);
    std::vector<std::pair<uint8_t,std::shared_ptr<Operator>>> vec(
        soldiers.begin(), soldiers.end());
    std::sort(vec.begin(), vec.end(), comparePosition);
    for (const auto &soldier : vec)
        soldier.second->render();
    for (const auto &enemy : enemies)
        enemy.second->render();
}

void GameSdl::update() {
    std::shared_ptr<Snapshot> snap = snapshotQueue.pop();
    for (auto &player : snap->getInfo())
        soldiers[player.getId()]->update(player.getPosition(),
                                                player.getState(),
                                                player.getHealth());
    for (auto &infected : snap->getEnemies())
        enemies[infected.getId()]->update(infected.getPosition(), infected.getState());
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

