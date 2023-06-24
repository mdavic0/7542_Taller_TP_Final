#include "GameDrawner.h"
#include "GameSdl.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include "Defines.h"
#include "Sdl.h"
#include "SdlImage.h"
#include "SdlTTF.h"
#include "SdlException.h"
#include "Configuration.h"
#include "ManagerMusic.h"
#include "Font.h"
#include "Lobby.h"
#include <map>

GameDrawner::GameDrawner(Queue<std::shared_ptr<Snapshot>> &snapshot_queue,
    Queue<std::shared_ptr<EventDTO>> &client_events, bool& error, int menu,
    uint8_t idPlayer, uint8_t numPlayers) : client_events(client_events),
    snapshot_queue(snapshot_queue), error(error), menu(menu),
    numPlayers(numPlayers), idPlayer(idPlayer) {
}

void GameDrawner::run() {
    try {
        Sdl sdlInit(SDL_INIT_EVERYTHING);

        SdlImage sdlImage(IMG_INIT_PNG);

        SdlTTF sdlttf;

        WindowSdl window(   "Left 4 Dead",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            1024,
                            768,
                            SDL_WINDOW_RESIZABLE);

        Renderer render(window, -1, SDL_RENDERER_ACCELERATED);

        Font font("assets/font/Futurot.ttf", 20);
        font.setHinting();
        bool initGame = true;

        ManagerMusic manager;
        manager.playMusic("lobby");

        Lobby lobby(window, render, font, snapshot_queue, client_events, menu,
                    initGame, idPlayer, numPlayers);
        lobby.initLobby();
        
        if (initGame) {
            ConfigGame config(lobby.getConfigSnap(), render, window, manager);
            
            GameSdl gameSdl(window, render, snapshot_queue, client_events,
                            error, idPlayer, font, config);
            
            manager.playMusic("game");
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

                if (1000 / 40 > processTime)
                    SDL_Delay(1000 / 40 - processTime);
            }
        }
        client_events.close();
    } catch (const SdlException &exc) {
        std::cerr << "Launcher: " << exc.what() << std::endl;
    } catch (const ClosedQueue& exc){
        client_events.close();
        this->error = true;
        std::cout << "Client sanp Queue closed, then events Queue is closed in GameDrawner " << std::endl;
    }
}

void GameDrawner::stop() {
}

GameDrawner::~GameDrawner() {
    join();
}