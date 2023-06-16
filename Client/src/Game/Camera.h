#ifndef CAMERA_GAME_H_
#define CAMERA_GAME_H_

#include "Operator.h"
#include "WindowSdl.h"
#include <map>
#include <memory>
#include <SDL2/SDL.h>

class Camera {
    private:
        std::pair<int16_t, int16_t> posCamera;
        WindowSdl& window;
    public:
        explicit Camera(WindowSdl& window);
        ~Camera();
        // Camera(const Camera& other) = delete;
        // Camera& operator=(const Camera&& other) = delete;
        void update(std::pair<int16_t, int16_t> posPlayer);
        int16_t getPosX();
        int16_t getPosY();
        int16_t getScaleX();
        int16_t getScaleY();
        SDL_Rect getRect();
};

#endif
