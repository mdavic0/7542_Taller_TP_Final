#ifndef _SDLTTF_H_
#define _SDLTTF_H_

#include <SDL2/SDL_ttf.h>

class SdlTTF {
    public:
        SdlTTF();
        ~SdlTTF();
        SdlTTF(const SdlTTF& other) = delete;
        SdlTTF& operator=(const SdlTTF& other) = delete;
        SdlTTF(SdlTTF&& other) = delete;
        SdlTTF& operator=(SdlTTF&& other) = delete;
};

#endif
