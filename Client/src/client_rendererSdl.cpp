#include "client_rendererSdl.h"

Renderer::Renderer(SDL_Window* window, int index, uint32_t flags) :
    render(nullptr) {
    this->render = SDL_CreateRenderer(window, index, flags);
    if (!this->render)
        throw std::runtime_error("Failed to create rendering context");
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
    SDL_RenderCopy(this->render, texture, &rectInit, &rectFinal);
}

SDL_Renderer* Renderer::get() {
    return this->render;
}
