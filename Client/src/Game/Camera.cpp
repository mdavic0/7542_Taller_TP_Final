#include "Camera.h"
#include "Defines.h"

Camera::Camera(WindowSdl& window) :
    posCamera({0, 0}),
    window(window) {
}

void Camera::update(std::pair<int16_t, int16_t> posPlayer) {

    this->posCamera.first = posPlayer.first - (window.getWidth() / 2); 
    this->posCamera.second = posPlayer.second - (window.getHeight() / 2); 

    if (posCamera.first < 0)
        posCamera.first = 0;
    if (posCamera.second < 0)
        posCamera.second = 0;
    if (posCamera.first > WINDOW_WIDTH - window.getWidth())
        posCamera.first = WINDOW_WIDTH - window.getWidth();
    if (posCamera.second > WINDOW_HEIGTH - window.getHeight())
        posCamera.second = WINDOW_HEIGTH - window.getHeight();
}

int16_t Camera::getPosX() {
    return this->posCamera.first;
}

int16_t Camera::getPosY() {
    return this->posCamera.second;
}

int16_t Camera::getScaleY() {
    return this->window.getHeight() / WINDOW_HEIGTH;
}

int16_t Camera::getScaleX() {
    return this->window.getHeight() / WINDOW_WIDTH;
}

SDL_Rect Camera::getRect() {
    return {posCamera.first,
            posCamera.second,
            1920,
            1080};
}

Camera::~Camera() {
}
