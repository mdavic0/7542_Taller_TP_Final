#include "client_gameSdl.h"
#include "client_handleEvent.h"
#include "common_defines.h"
#include "mapSdl.h"
#include <stdexcept>

GameSdl::GameSdl(int id, Queue<Snapshot*>& snapshotQueue,
    Queue<EventDTO*>& eventQueue, bool& endGame) : idOperator(id),
    snapshotQueue(snapshotQueue), eventQueue(eventQueue), endGame(endGame) {

    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
        throw std::runtime_error("Failed to init SDL");
    
    if(IMG_Init(IMG_INIT_PNG) < 0)
        throw std::runtime_error("Failed to init IMG_Init");
    
    this->window = SDL_CreateWindow("Left 4 Dead", 
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    WINDOW_WIDTH,
                                    WINDOW_HEIGTH,
                                    SDL_WINDOW_SHOWN);
    if (!this->window)
        throw std::runtime_error("Failed to create a window");
}

void GameSdl::run() {
    EventHandler event(this->eventQueue);
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    Operator soldier(idOperator, render);
    MapSdl map(0, render);
    while (event.isRunning()) { 
        uint32_t frameInit = SDL_GetTicks();

        render.clear();
        SDL_PumpEvents();
        event.listen();
        soldier.update(event.getMoveDirection());
        map.render();
        soldier.render();
        render.present();
        soldier.updateCurrentFrame();

        uint32_t frameEnd = SDL_GetTicks();
        uint32_t processTime = frameEnd - frameInit;

        if (1000 / 20 > processTime)
            SDL_Delay(1000 / 20 - processTime);
    }
    this->endGame = true;
    eventQueue.close();
}

GameSdl::~GameSdl() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    IMG_Quit();
}

