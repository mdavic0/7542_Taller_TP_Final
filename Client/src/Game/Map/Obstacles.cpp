#include "Obstacles.h"
#include "Defines.h"

Obstacles::Obstacles(TypeObstacle type, Renderer& render,
    std::pair<int16_t, int16_t> position, TextureManager& texture) :
    Object(), type(type), renderObstacle(render), position(position),
    texture(texture) {
}

int16_t Obstacles::getPosY() {
    return this->position.second;
}

void Obstacles::renderTire(SDL_Rect camera) {
    SDL_Rect rectInit = {0, 0, 228, 260};
    SDL_Rect rectFinal = {  position.first - camera.x + TIRE_WIDTH,
                            position.second - camera.y + TIRE_HEIGHT,
                            TIRE_WIDTH * 2, TIRE_HEIGHT * 2};
    this->renderObstacle.copy(texture.getTexture(type), rectInit,
                            rectFinal);
}

void Obstacles::renderCrater(SDL_Rect camera) {
    SDL_Rect rectInit = {0, 0, 392, 100};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y + (CRATER_HEIGHT * 2),
                            CRATER_WIDTH * 2, CRATER_HEIGHT};
    this->renderObstacle.copy(texture.getTexture(type), rectInit,
                            rectFinal);
}

void Obstacles::render(SDL_Rect camera) {
    switch (type) {
        case TypeObstacle::obstacle_tire:
            renderTire(camera);
            break;
        case TypeObstacle::obstacle_crater:
            renderCrater(camera);
            break;
        default:
            break;
    }
}

Obstacles::~Obstacles() {
}

