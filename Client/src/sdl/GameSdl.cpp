#include "GameSdl.h"
#include "Defines.h"
#include <iostream>

GameSdl::GameSdl(WindowSdl& window, Renderer& renderer,
    Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
    Queue<std::shared_ptr<EventDTO>>& eventQueue,
    bool& endGame, int id) : window(window), renderer(renderer),
    snapshotQueue(snapshotQueue), eventQueue(eventQueue), endGame(endGame),
    events(eventQueue), map(1, this->renderer), soldier(0, id, this->renderer) {
}

bool GameSdl::isRunning() {
    return this->events.isRunning();
}

void GameSdl::run() {
    // EventHandler event(this->eventQueue);
    // Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    // Operator soldier(0, idOperator, render);
    // MapSdl map(0, render);
    // eventQueue.push(new EventDTO(Event::event_start_game));
    // while (event.isRunning()) { 
    //     uint32_t frameInit = SDL_GetTicks();

    //     render.clear();
    //     SDL_PumpEvents();
    //     event.listen();
        // this.update();
        // soldier.update(event.getMoveDirection());
        // Snapshot* snap = snapshotQueue.pop();
        // // std::cout << snap->getPositions()[TypeOperator(1)].first << std::endl;
        // std::map<uint8_t, StOperator> players = snap->getInfo();
        // // std::cout << (int)players.size() << std::endl;
        // if (auto search = players.find(soldier.getId()); search != players.end()) {
        //         soldier.update(players.at(soldier.getId()).getPosition());
        //         //std::cout << "Actualizo la posicion\n";
        // }
        // map.render();
        // soldier.render();
        // render.present();

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
    std::shared_ptr<Snapshot> snap = snapshotQueue.pop();
    std::map<uint8_t, StOperator> players = snap->getInfo();
        // std::cout << (int)players.size() << std::endl;
    if (auto search = players.find(soldier.getId()); search != players.end()) {
            StOperator player = players.at(soldier.getId());
            soldier.update(player.getPosition(), player.getState());
            //std::cout << "Actualizo la posicion\n";
    }
}

void GameSdl::handleEvents() {
    this->events.listen();
}

GameSdl::~GameSdl() {
}

