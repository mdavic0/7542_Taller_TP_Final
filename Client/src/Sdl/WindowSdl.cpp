#include "WindowSdl.h"
#include "SdlException.h"

WindowSdl::WindowSdl(const std::string& title, int x, int y, int h, int w,
    uint32_t flags) : window(nullptr) {
    this->window = SDL_CreateWindow(title.c_str(), x, y, w, h, flags);
    if (this->window == nullptr)
        throw SdlException("Failed to create a window");
}

WindowSdl::WindowSdl(SDL_Window* window) : window(window) {
    if (this->window == nullptr)
        throw SdlException("Failed to create a window");
}

WindowSdl::WindowSdl(WindowSdl&& other) noexcept : window(other.window) {
    other.window = nullptr;
}

WindowSdl& WindowSdl::operator=(WindowSdl&& other) noexcept {
    if (&other == this)
        return *this;
    if (window != nullptr)
        SDL_DestroyWindow(window);
    window = other.window;
    other.window = nullptr;
    return *this;
}

WindowSdl::~WindowSdl() {
    if (this->window != nullptr)
        SDL_DestroyWindow(this->window);
}

SDL_Window* WindowSdl::getWindow() {
    return this->window;
}

int WindowSdl::getHeight() {
    int h;
    SDL_GetWindowSize(this->window, nullptr, &h);
    return h;
}

int WindowSdl::getWidth() {
    int w;
    SDL_GetWindowSize(this->window, &w, nullptr);
    return w;
}
