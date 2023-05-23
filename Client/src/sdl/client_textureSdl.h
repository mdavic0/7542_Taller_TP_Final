#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "client_rendererSdl.h"
#include <string>
#include <stdexcept>

class Texture {
    private:
        Renderer& textureRender;
        SDL_Texture* texture;
        void loadTexture(const std::string& file);
        void freeTexture();
    public:
        Texture(Renderer& renderer, const std::string& file);
        ~Texture();
        SDL_Texture* getTexture();
};

#endif
