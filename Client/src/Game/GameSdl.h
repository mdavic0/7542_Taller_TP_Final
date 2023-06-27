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
#include "Camera.h"
#include "Obstacles.h"
#include "ConfigGame.h"
#include "GrenadeSdl.h"
#include "ManagerMusic.h"
#include "EndGame.h"
#include <list>
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
        bool endGame;
        std::map<uint16_t, std::shared_ptr<Operator>>& soldiers;
        std::map<uint16_t, std::shared_ptr<Enemy>>& enemies;
        std::map<uint16_t, std::shared_ptr<Obstacles>>& obstacles;
        std::list<std::shared_ptr<GrenadeSdl>> grenades;
        Hud hud;
        uint16_t idPlayer;
        TypeGame mode;
        Font& font;
        Camera camera;
        TextureManager& textures;
        ManagerMusic& music;
        bool blitzAttack;
        EndGame endGameSdl;
        std::pair<int16_t, int16_t> calculateMassCenter();
        void updateGrenades(std::shared_ptr<Snapshot> snap);
        void renderBlitz();

    public:
        GameSdl(WindowSdl& window, Renderer& renderer,
                Queue<std::shared_ptr<Snapshot>>& snapshotQueue,
                Queue<std::shared_ptr<EventDTO>>& eventQueue,
                uint8_t idPlayer, Font& font, ConfigGame& config);
        ~GameSdl();
        void update();
        void render();
        bool isRunning();
        void handleEvents();
};

#endif
