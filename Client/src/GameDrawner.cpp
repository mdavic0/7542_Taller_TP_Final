#include "GameDrawner.h"
#include "GameSdl.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include "Defines.h"
#include "Sdl.h"
#include "SdlImage.h"
#include "SdlException.h"


GameDrawner::GameDrawner(Queue<Snapshot *> &snapshot_queue,
    Queue<EventDTO *> &client_events, bool& endGame) :
    client_events(client_events), snapshot_queue(snapshot_queue),
    endGame(endGame) {
}

void GameDrawner::run() {
    Sdl sdlInit(SDL_INIT_EVERYTHING);
    
    SdlImage sdlImage(IMG_INIT_PNG);

    WindowSdl window(   "Left 4 Dead", 
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED,
                        WINDOW_HEIGTH,
                        WINDOW_WIDTH,
                        SDL_WINDOW_SHOWN);

    Renderer render(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);

    // map<<typeOperator, state>, <x,y>> players = ;
    // map<<Enemys, state>, <position>>
    // int map;
    // int mode;
    GameSdl gameSdl(window, render, snapshot_queue, client_events, endGame, 1);
    // while (players.size() < 2) {
    //     render("Esperando jugadores");
    // }
    // try {
    client_events.push(new EventDTO(Event::event_start_game));
    while (gameSdl.isRunning()) { 
        uint32_t frameInit = SDL_GetTicks();

        render.clear();
        SDL_PumpEvents();
            gameSdl.update();
            gameSdl.handleEvents();
            gameSdl.render();
        render.present();

        uint32_t frameEnd = SDL_GetTicks();
        uint32_t processTime = frameEnd - frameInit;

        if (1000 / 20 > processTime)
            SDL_Delay(1000 / 20 - processTime);
    }
    this->endGame = true;
    client_events.close();
    // } catch (ClosedQueue &exc) {
    // } catch (...) {}
    /*while working
        handle_events() # popea de la queue de sdl y pushea a la queue de los sender
        ( o podría procesarlos directamente acá si son un evento que no modifica a los
        demas jugadores. Ejemplo: abrir un menu lateral, poner el juego en mute, etc.)

        process_events() #popea de la queue del receiver y procesa los eventos para
        actualizar el juego.

        render()

        sleep(delta_t)*/
}

void GameDrawner::stop() {
}
