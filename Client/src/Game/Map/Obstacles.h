#ifndef OBSTACLE_MAP_H_
#define OBSTACLE_MAP_H_

#include "TypeObstacle.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include "TextureManager.h"
#include "Object.h"
#include <optional>
#include <memory>
#include <SDL2/SDL.h>

class Obstacles : public Object {
    private:
        TypeObstacle type;
        Renderer& renderObstacle;
        std::pair<int16_t, int16_t> position;
        TextureManager& texture;
        WindowSdl& window;
        void renderTire(SDL_Rect camera);
        void renderCrater(SDL_Rect camera);
        bool verifyRender(SDL_Rect camera, SDL_Rect final);
    public:
        Obstacles(TypeObstacle type, Renderer& render,
                    std::pair<int16_t, int16_t> position,
                    TextureManager& texture, WindowSdl& window);
        ~Obstacles();
        void render(SDL_Rect camera) override;
        int16_t getPosY() override;
};

#endif
