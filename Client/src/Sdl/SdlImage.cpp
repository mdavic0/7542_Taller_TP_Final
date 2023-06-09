#include "SdlImage.h"
#include "SdlException.h"

SdlImage::SdlImage(uint32_t flags) {
    if(IMG_Init(flags) < 0)
        throw SdlException("Failed to init IMG_Init");
}

SdlImage::~SdlImage() {
    IMG_Quit();
}

