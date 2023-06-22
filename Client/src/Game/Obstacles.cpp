#include "Obstacles.h"

Obstacles::Obstacles(TypeObstacle type, Renderer& render,
    std::pair<int16_t, int16_t> position, TextureManager& texture) :
    type(type), renderObstacle(render),
    position(position), texture(texture), rectInit({}) {
    this->loadTexture();
    switch (type) {
        case TypeObstacle::obstacle_tire:
            rectInit = {0, 0, 228, 260};
            break;
        case TypeObstacle::obstacle_crater:
            rectInit = {0, 0, 392, 100};
            break;
        default:
            break;
    }
}

void Obstacles::loadTexture() {
    std::string path = "assets/images/sdl/obstacles/";
}

void Obstacles::render(SDL_Rect camera) {
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            200, 200};
    this->renderObstacle.copy(texture.getTexture(type), rectInit,
                            rectFinal);
}

Obstacles::~Obstacles() {
}

