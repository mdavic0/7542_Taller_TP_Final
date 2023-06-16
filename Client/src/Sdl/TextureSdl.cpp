#include "TextureSdl.h"
#include "Defines.h"
#include "SdlException.h"

Texture::Texture(Renderer& renderer, const std::string& file) :
    texture(nullptr) {
    this->loadTexture(file, renderer);    
}

Texture::Texture(Renderer& renderer, SDL_Surface* surface) :
    texture(nullptr) {
    this->texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    if (!texture)
        throw SdlException("Failed to create texture font");
    SDL_FreeSurface(surface);
}

Texture::Texture(Renderer& renderer, const std::string& file, SDL_Color c) :
    texture(nullptr) {
    this->freeTexture();
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface)
        throw SdlException("Error charge text ");
    if (SDL_SetSurfaceAlphaMod(surface, c.a) != 0)
        throw SdlException("Failed set Alpha texture ");
    if (SDL_SetSurfaceColorMod(surface, c.r, c.g, c.b) != 0)
        throw SdlException("Failed set color ");
    this->texture = SDL_CreateTextureFromSurface(renderer.get(), surface);
    if (!texture)
        throw SdlException("Error create texture");
    if (SDL_SetTextureAlphaMod(this->texture, c.a) != 0)
        throw SdlException("Failed set Alpha texture ");
    SDL_FreeSurface(surface);
}

void Texture::loadTexture(const std::string& file, Renderer& render) {
    this->freeTexture();
    SDL_Surface* surface = IMG_Load(file.c_str());
    if (!surface)
        throw SdlException("Error charge text");
    this->texture = SDL_CreateTextureFromSurface(render.get(), surface);
    if (!texture)
        throw SdlException("Error create texture");
    SDL_FreeSurface(surface);
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

Texture::Texture(Texture&& other) noexcept : texture(other.texture) {
    other.texture = nullptr;
}

Texture& Texture::operator=(Texture&& other) noexcept {
    if (&other == this)
        return *this;
    if (texture != nullptr)
        SDL_DestroyTexture(texture);
    texture = other.texture;
    other.texture = nullptr;
    return *this;
}

Texture::~Texture() {
    this->freeTexture();
}

