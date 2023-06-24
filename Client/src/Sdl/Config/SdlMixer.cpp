#include "SdlMixer.h"
#include "SdlException.h"

SdlMixer::SdlMixer(uint32_t flags) {
    if ((Mix_Init(flags) & flags) != flags)
        throw SdlException("Mix_Init");
}

SdlMixer::~SdlMixer() {
    while (Mix_Init(0))
        Mix_Quit();
}

