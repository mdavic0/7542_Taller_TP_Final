#ifndef OBSTACLE_MAP_H_
#define OBSTACLE_MAP_H_

#include "TypeObstacle.h"
#include "RendererSdl.h"
#include "TextureSdl.h"
#include <optional>
#include <memory>
#include <SDL2/SDL.h>

class Obstacles {
    private:
        TypeObstacle type;
        Renderer& renderObstacle;
        std::pair<int16_t, int16_t> position;
        std::optional<Texture> textureObstacle;
        SDL_Rect rectInit;
        void loadTexture();
    public:
        Obstacles(TypeObstacle type, Renderer& render,
                    std::pair<int16_t, int16_t> position);
        ~Obstacles();
        void render(SDL_Rect camera);
};

#endif
