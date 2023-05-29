#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "Move.h"
#include "States.h"
#include "TextureSdl.h"
#include "RendererSdl.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Operator {
    private:
        int operatorId;
        std::pair<int, int> position;
        std::map<std::string, Texture*> textures;
        States stateOperator;
        Renderer renderPlayer;
        int numFrames;
        int currentFrame;
        Uint32 lastUpdateTime;
        void chargeTexture(Renderer& renderer);
        void renderIdle();
        void renderMove();
        void setState(States state);
        int setNumFrames(States state);
    public:
        Operator(int id, Renderer& renderer);
        ~Operator();     
        void update(MoveTo direction);
        void updateCurrentFrame();
        void render();
};

#endif
