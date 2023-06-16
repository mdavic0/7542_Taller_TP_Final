#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "RendererSdl.h"
#include <string>
#include <stdexcept>

class Texture {
    private:
        SDL_Texture* texture;
        void loadTexture(const std::string& file, Renderer& render);
        void freeTexture();
    public:
        Texture(Renderer& renderer, const std::string& file);
        Texture(Renderer& renderer, const std::string& file, SDL_Color c);
        Texture(Renderer& renderer, SDL_Surface* surface);
        ~Texture();
        Texture(Texture&& other) noexcept;
        Texture& operator=(Texture&& other) noexcept;
        Texture(const Texture& other) = delete;
        Texture& operator=(const Texture& other) = delete;
        SDL_Texture* getTexture();
        int frames();
};

#endif
