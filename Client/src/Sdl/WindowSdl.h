#ifndef WINDOW_SDL_H_
#define WINDOW_SDL_H_

#include <SDL2/SDL.h>
#include <string>

class WindowSdl {
    private:
        SDL_Window* window;
    public:
        WindowSdl(const std::string& title, int x, int y, int h, int w,
                    uint32_t flags);
        ~WindowSdl();
        WindowSdl(SDL_Window* window);
        WindowSdl(WindowSdl&& other) noexcept;
        WindowSdl& operator=(WindowSdl&& other) noexcept;
        WindowSdl(const WindowSdl& other) = delete;
        WindowSdl& operator=(const WindowSdl& other) = delete; 
        SDL_Window* getWindow();
        int getWidth();
        int getHeight();
        void adjustedRect(SDL_Rect& rect, int w, int h);
};

#endif
