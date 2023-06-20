#include "WindowSdl.h"
#include "SdlException.h"
#include "Defines.h"

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

void WindowSdl::adjustedRect(SDL_Rect& rect) {
    int width = getWidth();
    float aspectRatio =
        static_cast<float>(rect.w) / static_cast<float>(rect.h);
    // Resolucion WIDTH_SCREEN_INIT a la que fue estandarizado para escalar
    float scaleFactorX =
        static_cast<float>(width) / static_cast<float>(WIDTH_SCREEN_INIT); 

    int newWidth = static_cast<int>(rect.w * scaleFactorX); 
    int newHeight = static_cast<int>(newWidth / aspectRatio);

    float positionRatio =
        static_cast<float>(rect.x) / static_cast<float>(rect.y);
    int newX = static_cast<int>(rect.x * scaleFactorX);
    int newY = static_cast<int>(newX / positionRatio);

    rect.x = newX;
    rect.y = newY;
    rect.w = newWidth;
    rect.h = newHeight;
}
