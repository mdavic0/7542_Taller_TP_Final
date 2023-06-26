#ifndef GRENADESDL_H_
#define GRENADESDL_H_

#include "TypeGrenade.h"
#include "GrenadeDto.h"
#include "RendererSdl.h"
#include "TextureManager.h"
#include "ManagerMusic.h"
#include <SDL2/SDL.h>

class GrenadeSdl {
    private:
        bool explotion;
        std::pair<int16_t, int16_t> position;
        TypeGrenade type;
        TextureManager& textures;
        Renderer& renderer;
        int numFrames;
        ManagerMusic& music;
        bool finishAnimation;
        void renderMovement(SDL_Rect camera);
        void renderExplotion(SDL_Rect camera);
        void playEffect();
    public:
        GrenadeSdl(GrenadeDto dto, TextureManager& textures, Renderer& render,
                    ManagerMusic& music);
        void update(GrenadeDto dto);
        void render(SDL_Rect camera);
        bool exploded();
        std::pair<int16_t, int16_t> getPosition();
        TypeGrenade getType();
        ~GrenadeSdl();
};

#endif
