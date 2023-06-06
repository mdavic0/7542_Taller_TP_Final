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
        void loadTextures();
    public:
        Hud(TypeOperator type, Renderer& render);
        ~Hud();
        void render();
};

#endif
