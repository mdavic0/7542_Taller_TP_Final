#ifndef SDLIMAGE_H_
#define SDLIMAGE_H_

#include <SDL2/SDL_image.h>
#include <cstdint>

class SdlImage {
    public:
        SdlImage(uint32_t flags);
        ~SdlImage();
        SdlImage(const SdlImage& other) = delete;
        SdlImage& operator=(const SdlImage& other) = delete;
        SdlImage(SdlImage&& other) = delete;
        SdlImage& operator=(SdlImage&& other) = delete;
};

#endif
