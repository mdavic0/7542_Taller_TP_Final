#ifndef GAME_SDL_H_
#define GAME_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "client_operator.h"
#include "client_rendererSdl.h"
#include "common_queue.h"
#include "common_snapshot.h" 
#include "common_eventdto.h" 

class GameSdl {
    private:
        SDL_Window* window;
        Queue<Snapshot*>& snapshotQueue;
        Queue<EventDTO*>& eventQueue;
        bool running;
        int idOperator;
        bool& endGame;
    public:
        GameSdl(int id, Queue<Snapshot*>& snapshotQueue,
                Queue<EventDTO*>& eventQueue, bool& endGame);
        ~GameSdl();
        void run();
};

#endif
