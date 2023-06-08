#ifndef HUD_H_
#define HUD_H_

#include "TypeOperator.h"
#include "RendererSdl.h"
#include "TextureSdl.h"
#include <map>

class Hud {
    private:
        TypeOperator type;
        Renderer& renderHud;
        std::map<std::string, Texture*> texturesHud;
        uint8_t healthInit;
        void loadTextures();
        void renderBg();
        void renderHealthBar();
        void renderHealthFill(uint8_t healthPlayer);
    public:
        Hud(TypeOperator type, Renderer& render);
        ~Hud();
        void render(uint8_t healthPlayer);
};

#endif
