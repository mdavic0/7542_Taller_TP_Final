#include "Operator.h"
#include "Defines.h"
#include <iostream>

Operator::Operator(int id, Renderer& renderer) : operatorId(TypeOperator(id)),
    position({568, 568}), renderPlayer(renderer), stateOperator(States::idle),
    numFrames(0), flipType(SDL_FLIP_NONE) {
    this->chargeTexture(renderer);
    this->setState(States::idle);
}

void Operator::update(MoveTo direction) {
    // cuando se actualice solo fijarese el eje x para cambiar el sdl_flip
    switch (direction) {
        case MoveTo::move_up:
            this->setState(States::moving);
            position.second--;
            break;
        case MoveTo::move_down:
            this->setState(States::moving);
            position.second++;
            break;
        case MoveTo::move_left:
            this->flipType = SDL_FLIP_HORIZONTAL;
            this->setState(States::moving);
            position.first--;
            break;
        case MoveTo::move_right:
            this->flipType = SDL_FLIP_NONE;
            this->setState(States::moving);
            position.first++;
            break;
        case MoveTo::move_idle:
            this->setState(States::idle);
            break;
        default:
            break;
    }
}

void Operator::updatePosition(std::pair<uint16_t, uint16_t> pos) {
    position.first = pos.first;
    position.second = pos.second;
}

TypeOperator Operator::getType() {
    return this->operatorId;
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/units/" + std::to_string((int)operatorId);
    textures["Idle"] = new Texture(renderer, path + "/Idle.png", false);
    textures["Run"] = new Texture(renderer, path + "/Run.png", false);
}

void Operator::setState(States state) {
    this->numFrames = setNumFrames(state);
    this->stateOperator = state;
}

int Operator::setNumFrames(States state) {
    switch (state) {
        case States::idle:
            return this->textures["Idle"]->frames();
        case States::moving:
            return this->textures["Run"]->frames();
        default:
            return 0;
    }
}

void Operator::render() {
    switch (stateOperator) {
        case States::idle:
            renderAnimation(SPEED_IDLE, textures["Idle"]->getTexture());
            break;
        case States::moving:
            renderAnimation(SPEED_RUN, textures["Run"]->getTexture());
            break;
        default:
            break;
    }
}

void Operator::renderAnimation(int speed, SDL_Texture* texture) {
    int speedAnimation = static_cast<int>((SDL_GetTicks() / speed) % numFrames);
    SDL_Rect rectInit = {   SIZE_SPRITE * speedAnimation,
                            0,
                            SIZE_SPRITE,
                            SIZE_SPRITE};
    SDL_Rect rectFinal = {  position.first,
                            position.second,
                            SIZE_SPRITE,
                            SIZE_SPRITE};
    this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

Operator::~Operator() {
    for (const auto &text: this->textures)
        delete text.second;
}

