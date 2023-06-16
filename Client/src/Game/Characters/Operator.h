#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Move.h"
#include "State.h"
#include "TypeOperator.h"
#include "TextureSdl.h"
#include "RendererSdl.h"
#include <SDL2/SDL.h>
#include <map>
#include <memory>
#include <string>
#include <iostream>

class Operator {
    private:
        uint8_t id;
        TypeOperator operatorId;
        std::pair<int16_t, int16_t> position;
        std::map<std::string, std::unique_ptr<Texture>> textures;
        State stateOperator;
        Renderer& renderPlayer;
        SDL_RendererFlip flipType;
        int numFrames;
        int health;
        void chargeTexture(Renderer& renderer);
        void renderAnimation(int speed, SDL_Texture* texture, SDL_Rect camera);
        void renderDead(int speed, SDL_Texture* texture, SDL_Rect camera);
        int setNumFrames(State state);
        bool animationDeadFinish;
        uint8_t munition;
    public:
        Operator(uint8_t id, TypeOperator op, Renderer& renderer);
        ~Operator();     
        void updateMove(MoveTo direction);
        void update(std::pair<int16_t, int16_t> pos, State state,
                    int health, uint8_t munition);
        TypeOperator getType();
        void setState(State state);
        uint8_t getId();
        uint8_t getHealth();
        int16_t getPosX();
        int16_t getPosY();
        uint8_t getMunition();
        std::pair<int16_t, int16_t> getPosition();
        void render(SDL_Rect camera);
        bool isDead();
};

#endif
