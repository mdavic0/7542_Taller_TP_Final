#include "Camera.h"
#include "Defines.h"

Camera::Camera(WindowSdl& window) :
    posCamera({window.getWidth(), window.getHeight()}),
    windowCamera(window) {
}

void Camera::update(std::pair<int16_t, int16_t> posPlayer) {

    this->posCamera.first = posPlayer.first - (windowCamera.getWidth() / 2); 
    this->posCamera.second = posPlayer.second - (windowCamera.getHeight() / 2); 

    if (posCamera.first < 0)
        posCamera.first = 0;
    if (posCamera.second < 0)
        posCamera.second = 0;
    if (posCamera.first > WINDOW_WIDTH - windowCamera.getWidth())
        posCamera.first = WINDOW_WIDTH - windowCamera.getWidth();
    if (posCamera.second > WINDOW_HEIGTH - windowCamera.getHeight())
        posCamera.second = WINDOW_HEIGTH - windowCamera.getHeight();
}

int16_t Camera::getPosX() {
    return this->posCamera.first;
}

int16_t Camera::getPosY() {
    return this->posCamera.second;
}

int16_t Camera::getScaleY() {
    return this->windowCamera.getHeight() / WINDOW_HEIGTH;
}

int16_t Camera::getScaleX() {
    return this->windowCamera.getHeight() / WINDOW_WIDTH;
}

SDL_Rect Camera::getRect() {
    return {posCamera.first,
            posCamera.second,
            windowCamera.getWidth(),
            windowCamera.getHeight()};
}

Camera::~Camera() {
}
