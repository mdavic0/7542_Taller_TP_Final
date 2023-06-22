#ifndef MAPSDL_H_
#define MAPDSL_H_

#include "TextureManager.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include <SDL2/SDL.h>

class MapSdl {
    private:
        TextureManager& textures;
        Renderer& renderMap;
        WindowSdl& window;
    public:
        MapSdl(TextureManager& textureManager, Renderer& render,
                WindowSdl& window);
        ~MapSdl();
        void render(SDL_Rect camera);
};

#endif
