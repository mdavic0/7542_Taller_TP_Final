#ifndef GAME_SDL_H_
#define GAME_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "client_operator.h"
#include "client_rendererSdl.h"
#include <optional>

class GameSdl {
    private:
        SDL_Window* window;
        std::optional<Renderer> renderer;
        bool running;
        int idOperator;
    public:
        explicit GameSdl(int id);
        ~GameSdl();
        void run();
};

#endif
