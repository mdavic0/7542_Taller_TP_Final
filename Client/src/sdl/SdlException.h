#ifndef SDL_EXCEPTION_H_
#define SDL_EXCEPTION_H_

#include "Exception.h"
#include <string>

class SdlException : public Exception {
    public:
        SdlException(const char* Description);
};

#endif
