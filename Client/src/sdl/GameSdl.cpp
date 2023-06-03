#include "GameSdl.h"
#include "Defines.h"
#include <iostream>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<Snapshot*>& snapshotQueue, Queue<EventDTO*>& eventQueue,
    bool& endGame, int id) : window(window), renderer(renderer),
    snapshotQueue(snapshotQueue), eventQueue(eventQueue), endGame(endGame),
    events(eventQueue), map(0, this->renderer), soldier(id, this->renderer) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::run() {
    //EventHandler event(this->eventQueue);
    //Operator soldier(idOperator, render);
    // MapSdl map(0, render);
    // eventQueue.push(new EventDTO(Event::event_start_game));
    // while (events.isRunning()) { 
    //     uint32_t frameInit = SDL_GetTicks();

    //     render.clear();
    //     SDL_PumpEvents();
    //     event.listen();
    //     // this.update();
    //     // soldier.update(event.getMoveDirection());
    //     Snapshot* snap = snapshotQueue.pop();
    //     // std::cout << snap->getPositions()[TypeOperator(1)].first << std::endl;
    //     std::map<TypeOperator, std::pair<uint16_t, uint16_t>> posi = snap->getPositions();
    //     // std::cout << (int)posi.size() << std::endl;
    //     // if (posi[soldier.getType()].first) {
    //             soldier.updatePosition(posi[soldier.getType()]);
    //             // std::cout << "Actualizo la posicion\n";
    //     // }
    //     map.render();
    //     soldier.render();
    //     render.present();

    //     uint32_t frameEnd = SDL_GetTicks();
    //     uint32_t processTime = frameEnd - frameInit;

    //     if (1000 / 20 > processTime)
    //         SDL_Delay(1000 / 20 - processTime);
    // }
    // this->endGame = true;
    // eventQueue.close();
}

void GameSdl::render() {
    this->map.render();
    this->soldier.render();
}

void GameSdl::update() {
    Snapshot* snap = snapshotQueue.pop();
    std::map<TypeOperator, std::pair<uint16_t, uint16_t>> posi = snap->getPositions();
    if (posi[soldier.getType()].first)
        soldier.updatePosition(posi[soldier.getType()]);
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

