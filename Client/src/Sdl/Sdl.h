#ifndef SDLINIT_H_
#define SDLINIT_H_

#include <SDL2/SDL.h>

class Sdl {
    public:
        Sdl(uint32_t flags);
        ~Sdl();
        Sdl(const Sdl& other) = delete;
        Sdl& operator=(const Sdl& other) = delete;
        Sdl(Sdl&& other) = delete;
        Sdl& operator=(Sdl&& other) = delete;
};

#endif
