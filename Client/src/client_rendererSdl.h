#ifndef RENDERER_SDL_H_
#define RENDERER_SDL_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdexcept>

class Renderer {
    private:
        SDL_Renderer* render;
    public:
        Renderer(SDL_Window* window, int index, uint32_t flags);
        ~Renderer();
        void clear();
        void present();
        void copy(SDL_Texture* texture, SDL_Rect& rectInit, 
                    SDL_Rect& rectFinal);
        SDL_Renderer* get();
};

#endif
