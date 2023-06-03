#ifndef WINDOW_SDL_H_
#define WINDOW_SDL_H_

#include <SDL2/SDL.h>
#include <string>

class WindowSdl {
    private:
        std::string title;
        int x;
        int y;
        int height;
        int width;
        uint32_t flags;
        SDL_Window* window;
    public:
        WindowSdl(const std::string& title, int x, int y, int h, int w,
                    uint32_t flags);
        ~WindowSdl();
        WindowSdl(const WindowSdl& other) = delete;
        WindowSdl& operator=(const WindowSdl& other) = delete; 
        SDL_Window* getWindow();
};

#endif
