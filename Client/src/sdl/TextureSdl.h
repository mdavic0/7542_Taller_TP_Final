#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RendererSdl.h"
#include <string>
#include <stdexcept>

class Texture {
    private:
        Renderer& textureRender;
        SDL_Texture* texture;
        void loadTexture(const std::string& file, bool resize);
        void freeTexture();
    public:
        Texture(Renderer& renderer, const std::string& file, bool resize);
        Texture(Renderer& renderer, const std::string& file, SDL_Color c);
        Texture(Renderer& renderer, SDL_Surface* surface);
        ~Texture();
        SDL_Texture* getTexture();
        int frames();
};

#endif
