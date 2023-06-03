#include "SdlException.h"
#include <SDL2/SDL.h>

SdlException::SdlException(const char* description) :
    Exception("%s [%s]", description, SDL_GetError()) {
}
