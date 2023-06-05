#include "TextureSdl.h"
#include "Defines.h"
#include "SdlException.h"

Texture::Texture(Renderer& renderer, const std::string& file, bool resize) :
    textureRender(renderer), texture(nullptr) {
    this->loadTexture(file, resize);    
}

void Texture::loadTexture(const std::string& file, bool resize) {
    this->freeTexture();
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface)
        throw SdlException("Error charge text");
    SDL_Surface* resized = nullptr;
    if (resize) {
        resized = SDL_CreateRGBSurface(0, WINDOW_WIDTH, WINDOW_HEIGTH,
                                                surface->format->BitsPerPixel,
                                                surface->format->Rmask,
                                                surface->format->Gmask,
                                                surface->format->Bmask,
                                                surface->format->Amask);
        SDL_BlitScaled(surface, nullptr, resized, nullptr);
    }

    SDL_Renderer* render = this->textureRender.get();
    if (resize)
        this->texture = SDL_CreateTextureFromSurface(render, resized);
    else
        this->texture = SDL_CreateTextureFromSurface(render, surface);
    if (!texture)
        throw SdlException("Error create texture");
    SDL_FreeSurface(surface);
    if (resize)
        SDL_FreeSurface(resized);
}

int Texture::frames() {
    int w, h;
    if (SDL_QueryTexture(this->texture, nullptr, nullptr, &w, &h) != 0)
        throw SdlException("Error in number frames");
    return (int)w/h;
}

SDL_Texture* Texture::getTexture() {
    return this->texture;
}

void Texture::freeTexture() {
    if (this->texture) {
        SDL_DestroyTexture(this->texture);
        this->texture= nullptr;
    }
}

Texture::~Texture() {
    this->freeTexture();
}

