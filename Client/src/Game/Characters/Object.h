#ifndef OBJECT_H_
#define OBJECT_H_

#include <cstdint>
#include <utility>
#include <SDL2/SDL.h>

class Object {
    public:
        Object() {}
        ~Object() {}
        virtual int16_t getPosY() = 0;
        virtual void render(SDL_Rect Camera) = 0;
};

#endif
