#include "client_operator.h"

Operator::Operator(int id, Renderer& renderer) : operatorId(id), posX(0),
    posY(0), renderPlayer(renderer) {
    this->chargeTexture(renderer);
}

void Operator::move(MoveTo direction) {
    switch (direction) {
        case MoveTo::move_up:
            posY--;
            break;
        case MoveTo::move_down:
            posY++;
            break;
        case MoveTo::move_left:
            posX--;
            break;
        case MoveTo::move_right:
            posX++;
            break;
        default:
            break;
    }
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/units/" + std::to_string(operatorId);
    textures["Idle"] = new Texture(renderer, path + "/Idle.png");
}

void Operator::render() {
    SDL_Rect rectInit = {0, 0, 128, 128};
    SDL_Rect rectFinal = {posX, posY, 128, 128};
    SDL_Texture* textureIdle = textures["Idle"]->getTexture();
    this->renderPlayer.copy(textureIdle, rectInit, rectFinal);
}

Operator::~Operator() {
}

