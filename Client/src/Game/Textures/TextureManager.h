#ifndef TEXTURE_MANAGER_H_
#define TEXTURE_MANAGER_H_

#include "TextureSdl.h"
#include "RendererSdl.h"
#include "TypeInfected.h"
#include "TypeObstacle.h"
#include <map>
#include <memory>
#include <string>

class TextureManager {
    private:
        std::map<std::string, std::shared_ptr<Texture>> mapTextures;
        void loadTextures(Renderer& render, uint8_t idMap);
    public:
        TextureManager(Renderer& render, uint8_t idMap);
        ~TextureManager();
        SDL_Texture* getTexture(TypeInfected type, std::string nameTexture);
        SDL_Texture* getTexture(TypeObstacle type);
        SDL_Texture* getTexture(std::string nameTexture);
        int getFrames(TypeInfected type, std::string nameTexture);

};

#endif
