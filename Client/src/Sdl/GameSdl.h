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
#include "Hud.h"
#include "TypeGame.h"
#include "Font.h"
#include "Enemy.h"
#include <memory>
#include <map>

class GameSdl {
    private:
        WindowSdl& window;
        Renderer& renderer;
        EventHandler events;
        Queue<std::shared_ptr<Snapshot>>& snapshotQueue;
        Queue<std::shared_ptr<EventDTO>>& eventQueue;
        MapSdl map;
        bool& endGame;
        std::map<uint8_t, std::shared_ptr<Operator>>& soldiers;
        std::map<uint8_t, std::shared_ptr<Enemy>>& enemies;
        Hud hud;
        uint8_t idPlayer;
        TypeGame mode;
        Font& font;

    public:
        GameSdl(WindowSdl& window, Renderer& renderer,
                Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
                Queue<std::shared_ptr<EventDTO>>& eventQueue, bool& endGame,
                std::map<uint8_t, std::shared_ptr<Operator>>& soldiers,
                uint8_t idPlayer, uint8_t idMap, TypeGame mode, Font& font,
                std::map<uint8_t, std::shared_ptr<Enemy>>& enemies);
        ~GameSdl();
        void update();
        void render();
        bool isRunning();
        void handleEvents();
};

#endif
