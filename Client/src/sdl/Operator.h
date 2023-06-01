#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Move.h"
#include "States.h"
#include "TypeOperator.h"
#include "TextureSdl.h"
#include "RendererSdl.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Operator {
    private:
        TypeOperator operatorId;
        std::pair<int, int> position;
        std::map<std::string, Texture*> textures;
        States stateOperator;
        Renderer renderPlayer;
        SDL_RendererFlip flipType;
        int numFrames;
        void chargeTexture(Renderer& renderer);
        void renderAnimation(int speed, SDL_Texture* texture);
        void setState(States state);
        int setNumFrames(States state);
    public:
        Operator(int id, Renderer& renderer);
        ~Operator();     
        void update(MoveTo direction);
        void updatePosition(std::pair<uint16_t, uint16_t> pos);
        TypeOperator getType();
                void render();
};

#endif
