#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Move.h"
#include "State.h"
#include "TypeOperator.h"
#include "TextureSdl.h"
#include "WindowSdl.h"
#include "RendererSdl.h"
#include "OperatorDto.h"
#include "Object.h"
#include "ManagerMusic.h"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <iostream>

class Operator : public Object {
    private:
        uint16_t id;
        TypeOperator operatorId;
        std::pair<int16_t, int16_t> position;
        std::map<std::string, std::unique_ptr<Texture>> textures;
        State stateOperator;
        Renderer& renderPlayer;
        SDL_RendererFlip flipType;
        int numFrames;
        int16_t health;
        bool animationDeadFinish;
        uint8_t munition;
        WindowSdl& window;
        ManagerMusic& music;
        bool stopGrenade;
        bool grenadeAvailable;
        bool smokeAvailable;
        void chargeTexture(Renderer& renderer);
        void renderAnimation(int speed, SDL_Texture* texture, SDL_Rect camera);
        void renderGrenade(int speed, SDL_Texture* texture, SDL_Rect camera);
        void renderStopGrenade(int speed, SDL_Texture* texture, SDL_Rect camera);
        void renderDead(int speed, SDL_Texture* texture, SDL_Rect camera);
        void renderIconInjure(SDL_Rect camera);
        void renderMusic();
        int setNumFrames(State state);
        bool verifyRender(SDL_Rect camera, SDL_Rect final);
        
    public:
        Operator(uint16_t id, TypeOperator op, Renderer& renderer,
                WindowSdl& window, ManagerMusic& music);
        ~Operator();     
        void updateMove(MoveTo direction);
        void update(std::pair<int16_t, int16_t> pos, State state,
                    int health, uint8_t munition);
        void update(StOperator snap);
        TypeOperator getType();
        void setState(State state);
        uint16_t getId();
        uint16_t getHealth();
        int16_t getPosX();
        int16_t getPosY() override;
        uint8_t getMunition();
        State getState();
        std::pair<int16_t, int16_t> getPosition();
        void render(SDL_Rect camera) override;
        bool isDead();
        bool getGrenadeAvailable();
        bool getSmokeAvailable();
};

#endif
