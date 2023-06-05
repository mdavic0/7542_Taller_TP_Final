#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Move.h"
#include "State.h"
#include "TypeOperator.h"
#include "TextureSdl.h"
#include "RendererSdl.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Operator {
    private:
        uint8_t id;
        TypeOperator operatorId;
        std::pair<uint16_t, uint16_t> position;
        std::map<std::string, Texture*> textures;
        State stateOperator;
        Renderer renderPlayer;
        SDL_RendererFlip flipType;
        int numFrames;
        void chargeTexture(Renderer& renderer);
        void renderAnimation(int speed, SDL_Texture* texture);
        void setState(State state);
        int setNumFrames(State state);
    public:
        Operator(uint8_t id, TypeOperator op, Renderer& renderer);
        ~Operator();     
        void updateMove(MoveTo direction);
        void update(std::pair<uint16_t, uint16_t> pos, State state);
        TypeOperator getType();
        uint8_t getId();
        void render();
};

#endif
