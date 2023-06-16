#include "RendererSdl.h"
#include "SdlException.h"

Renderer::Renderer(WindowSdl& window, int index, uint32_t flags) :
    render(nullptr) {
    this->render = SDL_CreateRenderer(window.getWindow(), index, flags);
    if (!this->render)
        throw SdlException("Failed to create rendering context");
}

Renderer::~Renderer() {
    if (this->render) {
        SDL_DestroyRenderer(this->render);
        this->render = nullptr;
    }
}

Renderer::Renderer(Renderer&& other) noexcept : render(other.render) {
    other.render = nullptr;
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
    if (&other == this)
        return *this;
    if (render != nullptr)
        SDL_DestroyRenderer(render);
    render = other.render;
    other.render = nullptr;
    return *this;
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

void Renderer::copyMap(SDL_Texture* texture, SDL_Rect& rectInit) {
    if (SDL_RenderCopy(this->render, texture, &rectInit, nullptr) != 0)
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
