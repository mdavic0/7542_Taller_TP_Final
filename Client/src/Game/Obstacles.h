#ifndef OBSTACLE_MAP_H_
#define OBSTACLE_MAP_H_

#include "TypeObstacle.h"
#include "RendererSdl.h"
#include "TextureManager.h"
#include <optional>
#include <memory>
#include <SDL2/SDL.h>

class Obstacles {
    private:
        TypeObstacle type;
        Renderer& renderObstacle;
        std::pair<int16_t, int16_t> position;
        TextureManager& texture;
        SDL_Rect rectInit;
        void loadTexture();
        void renderTire();
        void renderCrater();
    public:
        Obstacles(TypeObstacle type, Renderer& render,
                    std::pair<int16_t, int16_t> position,
                    TextureManager& texture);
        ~Obstacles();
        void render(SDL_Rect camera);
};

#endif
