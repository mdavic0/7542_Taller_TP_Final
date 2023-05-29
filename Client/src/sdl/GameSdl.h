#ifndef GAME_SDL_H_
#define GAME_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Operator.h"
#include "RendererSdl.h"
#include "Queue.h"
#include "Snapshot.h"
#include "EventDTO.h"

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
