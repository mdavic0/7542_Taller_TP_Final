#include "client_gameSdl.h"
#include "client_handleEvent.h"
#include "common_defines.h"
#include <stdexcept>

GameSdl::GameSdl(int id) : idOperator(id), renderer(std::nullopt) {
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

    this->renderer = std::make_optional<Renderer>(window, -1, SDL_RENDERER_ACCELERATED);   
}

void GameSdl::run() {
    EventHandler event;
    Renderer render(window, -1, SDL_RENDERER_ACCELERATED);
    Operator soldier(idOperator, render);
    while (event.isRunning()) { 
        uint32_t frameInit = SDL_GetTicks();
        SDL_PumpEvents();
        event.listen();
        soldier.move(event.getMoveDirection());
        render.clear();
        soldier.render();
        render.present();
        uint32_t frameEnd = SDL_GetTicks();
        uint32_t processTime = frameEnd - frameInit;
        if (1000 / 60 > processTime)
            SDL_Delay(1000/60 - processTime);
    }
}

GameSdl::~GameSdl() {
    SDL_DestroyWindow(this->window);
    SDL_Quit();
    IMG_Quit();
}

