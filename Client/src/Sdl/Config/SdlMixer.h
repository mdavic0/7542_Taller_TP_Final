#ifndef SDLMIXER_H_
#define SDLMIXER_H_

#include <SDL2/SDL_mixer.h>

class SdlMixer {
    public:
        SdlMixer(uint32_t flags);
        ~SdlMixer();
        SdlMixer(const SdlMixer& other) = delete;
        SdlMixer& operator=(const SdlMixer& other) = delete;
        SdlMixer(SdlMixer&& other) = delete;
        SdlMixer& operator=(SdlMixer&& other) = delete;
};

#endif
