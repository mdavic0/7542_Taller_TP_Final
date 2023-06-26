#ifndef ENDGAME_H_
#define ENDGAME_H_

#include "Font.h"
#include "RendererSdl.h"
#include "TextureManager.h"
#include "TypeGame.h"

class EndGame {
    private:
        Font& font;
        Renderer& renderer;
        TextureManager& textures;
        TypeGame type;
        WindowSdl& window;
        void renderClearZone();
        void renderSurvival();
    public:
        EndGame(Font& font, Renderer& renderer, TextureManager& textures,
                TypeGame type, WindowSdl& window);
        ~EndGame();
        void render();
};

#endif
