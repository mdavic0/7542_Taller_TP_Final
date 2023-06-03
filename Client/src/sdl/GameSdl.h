#ifndef GAME_SDL_H_
#define GAME_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Operator.h"
#include "RendererSdl.h"
#include "Queue.h"
#include "Snapshot.h"
#include "EventDTO.h"
#include "WindowSdl.h"
#include "HandleEvent.h"
#include "mapSdl.h"

class GameSdl {
    private:
        WindowSdl& window;
        Renderer& renderer;
        EventHandler events;
        Queue<Snapshot*>& snapshotQueue;
        Queue<EventDTO*>& eventQueue;
        MapSdl map;
        bool running;
        Operator soldier;
        bool& endGame;
    public:
        GameSdl(WindowSdl& window, Renderer& renderer, Queue<Snapshot*>& snapshotQueue,
                Queue<EventDTO*>& eventQueue, bool& endGame, int id);
        ~GameSdl();
        void run();
        void update();
        void render();
        bool isRunning();
        void handleEvents();
};

#endif
