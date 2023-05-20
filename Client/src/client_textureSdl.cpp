#include "client_textureSdl.h"

Texture::Texture(Renderer& renderer, const std::string& file) :
    textureRender(renderer), texture(nullptr) {
    this->loadTexture(file);    
}

void Texture::loadTexture(const std::string& file) {
    this->freeTexture();
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface)
        throw std::runtime_error("Error charge texture: " + 
                                std::string(IMG_GetError()));
    SDL_Renderer* render = this->textureRender.get();
    this->texture = SDL_CreateTextureFromSurface(render, surface);
    if (!texture)
        throw std::runtime_error("Error create texture: " + 
                                std::string(IMG_GetError()));
    SDL_FreeSurface(surface);
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

