#include "SdlTTF.h"
#include "SdlException.h"

SdlTTF::SdlTTF() {
    if (TTF_Init() != 0)
        throw SdlException("TTF_Init");
}

SdlTTF::~SdlTTF() {
    TTF_Quit();
}
