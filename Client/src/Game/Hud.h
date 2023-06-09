#ifndef HUD_H_
#define HUD_H_

#include "TypeOperator.h"
#include "RendererSdl.h"
#include "TextureSdl.h"
#include "Font.h"
#include <map>

class Hud {
    private:
        TypeOperator type;
        Renderer& renderHud;
        std::map<std::string, Texture*> texturesHud;
        uint8_t healthInit;
        Font& fontHud;
        void loadTextures();
        void renderBg();
        void renderHealthBar();
        void renderHealthIcon();
        void renderHealthFill(uint8_t healthPlayer);
        void renderIconWeapon();
        void renderIconBullet();
        void renderNumBullet(int numBullet);

    public:
        Hud(TypeOperator type, Renderer& render, Font& font);
        ~Hud();
        void render(uint8_t healthPlayer, int numBullet);
};

#endif
