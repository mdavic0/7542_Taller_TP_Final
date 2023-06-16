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

void WindowSdl::adjustedRect(SDL_Rect& rect, int w, int h) {
    int width = getWidth();
    int height = getHeight();
    float aspectRatio = static_cast<float>(rect.w) / static_cast<float>(rect.h);
    float scaleFactorX = static_cast<float>(width) / static_cast<float>(1440); // Resolucion a la que fue estandarizado
    float scaleFactorY = static_cast<float>(height) / static_cast<float>(900); // Resolucion a la que fue estandarizado

    int newWidth = static_cast<int>(rect.w * scaleFactorX); 
    int newHeight = static_cast<int>(newWidth / aspectRatio);
    int newX = static_cast<int>(rect.x * scaleFactorX);
    int newY = static_cast<int>(rect.y * scaleFactorY);

    // int oX = static_cast<int>((newX + rect.x) / 2);
    // int oY = static_cast<int>((newY + rect.y) / 2);

    rect.x = newX;
    rect.y = newY;
    rect.w = newWidth;
    rect.h = newHeight;

}
