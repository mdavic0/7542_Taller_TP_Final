#include "Operator.h"
#include <iostream>

Operator::Operator(int id, Renderer& renderer) : operatorId(id),
    position({568, 568}), renderPlayer(renderer), stateOperator(States::idle),
    numFrames(0), currentFrame(0), lastUpdateTime(SDL_GetTicks()) {
    this->chargeTexture(renderer);
    this->setState(States::idle);
}

void Operator::update(MoveTo direction) {
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
            this->setState(States::moving);
            position.first--;
            break;
        case MoveTo::move_right:
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

void Operator::updateCurrentFrame() {
    Uint32 currentTime = SDL_GetTicks();
    Uint32 elapsedTime = currentTime - lastUpdateTime;
    if (elapsedTime >= 60) {
        this->currentFrame = (this->currentFrame + 1) % this->numFrames;
        std::cout << "current frames: "<< this->currentFrame << std::endl;
        lastUpdateTime = currentTime;
    }
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/units/" + std::to_string(operatorId);
    textures["Idle"] = new Texture(renderer, path + "/Idle.png", false);
    textures["Run"] = new Texture(renderer, path + "/Run.png", false);
}

void Operator::setState(States state) {
    // if (this->stateOperator != state) {
        this->numFrames = setNumFrames(state);
        this->stateOperator = state;
        this->currentFrame = 0;
        this->lastUpdateTime = SDL_GetTicks();
    // }
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
            renderIdle();
            break;
        case States::moving:
            renderMove();
            break;
        default:
            break;
    }
}

void Operator::renderIdle() {
    SDL_Rect rectInit = {128*currentFrame, 0, 128, 128};
    SDL_Rect rectFinal = {position.first, position.second, 128, 128};
    SDL_Texture* textureIdle = textures["Idle"]->getTexture();
    this->renderPlayer.copy(textureIdle, rectInit, rectFinal);
}

void Operator::renderMove() {
    SDL_Rect rectInit = {128*currentFrame, 0, 128, 128};
    SDL_Rect rectFinal = {position.first, position.second, 128, 128};
    SDL_Texture* textureIdle = textures["Run"]->getTexture();
    this->renderPlayer.copy(textureIdle, rectInit, rectFinal);
}

Operator::~Operator() {
    for (const auto &text: this->textures)
        delete text.second;
}

