#include "WindowSdl.h"
#include "SdlException.h"

WindowSdl::WindowSdl(const std::string& title, int x, int y, int h, int w,
    uint32_t flags) : title(title), x(x), y(y), height(h), width(w),
    flags(flags) {
    this->window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
    if (this->window == nullptr)
        throw SdlException("Failed to create a window");
}

WindowSdl::~WindowSdl() {
    if (this->window != nullptr)
        SDL_DestroyWindow(this->window);
}

SDL_Window* WindowSdl::getWindow() {
    return this->window;
}
