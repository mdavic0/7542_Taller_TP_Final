#ifndef HUD_H_
#define HUD_H_

#include "TypeOperator.h"
#include "TypeGame.h"
#include "RendererSdl.h"
#include "TextureSdl.h"
#include "WindowSdl.h"
#include "Font.h"
#include <map>
#include <memory>

class Hud {
    private:
        TypeOperator type;
        TypeGame gameType;
        Renderer& renderHud;
        std::map<std::string, std::unique_ptr<Texture>> texturesHud;
        uint8_t healthInit;
        uint8_t munitionInit;
        Font& fontHud;
        uint8_t enemiesDeath;
        WindowSdl& window;
        void loadTextures();
        void renderBg();
        void renderHealthBar();
        void renderHealthIcon();
        void renderHealthFill(uint8_t healthPlayer);
        void renderIconWeapon();
        void renderIconBullet();
        void renderNumBullet(int numBullet);
        void renderBgMode();
        void renderTextMode(size_t size);

    public:
        Hud(TypeOperator type, TypeGame game, Renderer& render, Font& font, WindowSdl& window);
        ~Hud();
        void render(uint8_t healthPlayer, int numBullet, size_t size);
};

#endif
