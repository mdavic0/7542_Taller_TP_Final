#ifndef ENEMY_H_
#define ENEMY_H_

#include "RendererSdl.h"
#include "TextureSdl.h"
#include "State.h"
#include "TypeInfected.h"
#include <map>
#include <memory>

class Enemy {
    private:
        Renderer& renderEnemy;
        std::map<std::string, std::unique_ptr<Texture>> textures;
        std::pair<int16_t, int16_t> position;
        TypeInfected type;
        State stateEnemy;
        SDL_RendererFlip flipType;
        int numFrames;
        void chargeTextures();
        void setState(State state);
        int setNumFrames(State state);
        void renderAnimation(int speed, SDL_Texture* texture);

    public:
        Enemy(Renderer& render, TypeInfected type);
        ~Enemy();
        void update(std::pair<int16_t, int16_t> pos, State state);
        void render();
};

#endif
