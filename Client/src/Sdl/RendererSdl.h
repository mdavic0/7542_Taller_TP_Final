#ifndef RENDERER_SDL_H_
#define RENDERER_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "WindowSdl.h"

class Renderer {
    private:
        SDL_Renderer* render;
    public:
        Renderer(WindowSdl& window, int index, uint32_t flags);
        ~Renderer();
        Renderer(Renderer&& other) noexcept;
        Renderer& operator=(Renderer&& other) noexcept;
        Renderer(const Renderer& other) = delete;
        Renderer& operator=(const Renderer& other) = delete;
        void clear();
        void present();
        void copy(SDL_Texture* texture, SDL_Rect& rectInit, 
                    SDL_Rect& rectFinal);
        void copyFont(SDL_Texture* texture, SDL_Rect& rectFinal);
        void copy(SDL_Texture* texture, SDL_Rect& rectInit, 
                    SDL_Rect& rectFinal, const SDL_RendererFlip& flipType);
        SDL_Renderer* get();
};

#endif
