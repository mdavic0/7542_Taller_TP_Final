#include "RendererSdl.h"
#include "SdlException.h"

Renderer::Renderer(SDL_Window* window, int index, uint32_t flags) :
    render(nullptr) {
    this->render = SDL_CreateRenderer(window, index, flags);
    if (!this->render)
        throw SdlException("Failed to create rendering context");
}

Renderer::~Renderer() {
    if (this->render) {
        SDL_DestroyRenderer(this->render);
        this->render = nullptr;
    }
}

void Renderer::clear() {
    SDL_RenderClear(this->render);
}

void Renderer::present() {
    SDL_RenderPresent(this->render);
}

void Renderer::copy(SDL_Texture* texture, SDL_Rect& rectInit, 
    SDL_Rect& rectFinal) {
    if (SDL_RenderCopy(this->render, texture, &rectInit, &rectFinal) != 0)
        throw SdlException("Failed RenderCopy");
}

void Renderer::copyFont(SDL_Texture* texture, SDL_Rect& rectFinal) {
    if (SDL_RenderCopy(this->render, texture, nullptr, &rectFinal) != 0)
        throw SdlException("Failed RenderCopy Font");
}

void Renderer::copy(SDL_Texture* texture, SDL_Rect& rectInit,
    SDL_Rect& rectFinal, const SDL_RendererFlip& flipType) {
    if (SDL_RenderCopyEx(this->render, texture, &rectInit, &rectFinal, 0,
        nullptr, flipType) != 0)
        throw SdlException("Failed RenderCopyEx");
}

SDL_Renderer* Renderer::get() {
    return this->render;
}
