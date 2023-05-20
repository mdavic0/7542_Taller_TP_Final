#ifndef OPERATOR_H_
#define OPERATOR_H_

#include "common_move.h"
#include "client_textureSdl.h"
#include "client_rendererSdl.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class Operator {
    private:
        int operatorId;
        int posX;
        int posY;
        std::map<std::string, Texture*> textures;
        void chargeTexture(Renderer& renderer);
        Renderer renderPlayer;
    public:
        Operator(int id, Renderer& renderer);
        ~Operator();     
        void move(MoveTo direction);
        void render();
};

#endif
