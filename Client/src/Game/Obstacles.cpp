#include "Obstacles.h"

Obstacles::Obstacles(TypeObstacle type, Renderer& render,
    std::pair<int16_t, int16_t> position) : type(type), renderObstacle(render),
    position(position), textureObstacle(std::nullopt), rectInit({}) {
    this->loadTexture();
}

void Obstacles::loadTexture() {
    std::string path = "assets/images/sdl/obstacles/";
    switch (type) {
        case TypeObstacle::obstacle_tire:
            this->textureObstacle = Texture(renderObstacle,
                                        path + "tire.png");
            rectInit = {0, 0, 228, 260};
            break;
        case TypeObstacle::obstacle_crater:
            this->textureObstacle = Texture(renderObstacle,
                                        path + "crater.png");
            rectInit = {0, 0, 392, 100};
            break;
        default:
            break;
    }
}

void Obstacles::render(SDL_Rect camera) {
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            200, 200};
    this->renderObstacle.copy(textureObstacle->getTexture(), rectInit,
                            rectFinal);
}

Obstacles::~Obstacles() {
}

