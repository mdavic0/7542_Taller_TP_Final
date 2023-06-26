#ifndef BLITZ_SDL_H_
#define BLITZ_SDL_H_

#include "RendererSdl.h"
#include "TextureManager.h"
#include "ManagerMusic.h"
#include "WindowSdl.h"

class BlitzSdl {
    private:
        Renderer& renderer;
        TextureManager& textures;
        ManagerMusic& music;
        WindowSdl& window;
        int numFrames;
        int speedAnimation;
        void renderExplotion(int i, SDL_Rect camera);
    public:
        BlitzSdl(Renderer& render, TextureManager& textures,
                ManagerMusic& music, WindowSdl& window);
        void render(SDL_Rect camera);
        ~BlitzSdl();
};

#endif
