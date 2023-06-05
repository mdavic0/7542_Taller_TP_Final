#include "Sdl.h"
#include "SdlException.h"

Sdl::Sdl(uint32_t flags) {
    if (SDL_Init(flags) != 0)
        throw SdlException("Failed to init SDL");
}

Sdl::~Sdl() {
    SDL_Quit();
}

