#ifndef ENEMY_H_
#define ENEMY_H_

#include "RendererSdl.h"
#include "WindowSdl.h"
#include "State.h"
#include "TypeInfected.h"
#include "TextureManager.h"
#include "ManagerMusic.h"
#include "Object.h"
#include <map>
#include <memory>

class Enemy : public Object {
    private:
        Renderer& renderEnemy;
        std::pair<int16_t, int16_t> position;
        TypeInfected type;
        State stateEnemy;
        SDL_RendererFlip flipType;
        int numFrames;
        TextureManager& textures;
        WindowSdl& window;
        ManagerMusic& music;
        bool animationDeadFinish;
        int setNumFrames(State state);
        void renderAnimation(int speed, SDL_Texture* texture, SDL_Rect camera);
        bool verifyRender(SDL_Rect camera, SDL_Rect final);
        void renderDead(int speed, SDL_Texture* texture, SDL_Rect camera);

    public:
        Enemy(TextureManager& textures, Renderer& render, TypeInfected type,
            WindowSdl& window, ManagerMusic& music);
        ~Enemy();
        void update(std::pair<int16_t, int16_t> pos, State state);
        void render(SDL_Rect camera) override;
        void setState(State state);
        bool isDeadFinish();
        int16_t getPosY() override;
};

#endif
