#include "Operator.h"
#include "Defines.h"
#include <iostream>

Operator::Operator(uint8_t id, TypeOperator op, Renderer& renderer) : id(id), operatorId(op),
    position({0, 0}), renderPlayer(renderer), stateOperator(State::idle),
    numFrames(0), flipType(SDL_FLIP_NONE) {
    this->chargeTexture(renderer);
    this->setState(State::idle);
}

void Operator::updateMove(MoveTo direction) {
    // cuando se actualice solo fijarese el eje x para cambiar el sdl_flip
    switch (direction) {
        case MoveTo::move_up:
            this->setState(State::moving);
            position.second--;
            break;
        case MoveTo::move_down:
            this->setState(State::moving);
            position.second++;
            break;
        case MoveTo::move_left:
            this->flipType = SDL_FLIP_HORIZONTAL;
            this->setState(State::moving);
            position.first--;
            break;
        case MoveTo::move_right:
            this->flipType = SDL_FLIP_NONE;
            this->setState(State::moving);
            position.first++;
            break;
        case MoveTo::move_idle:
            this->setState(State::idle);
            break;
        default:
            break;
    }
}

void Operator::update(std::pair<uint16_t, uint16_t> pos, State state) {
    this->setState(state);
    if (pos.first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (pos.first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = pos;
}

TypeOperator Operator::getType() {
    return this->operatorId;
}

uint8_t Operator::getId() {
    return this->id;
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/units/" + std::to_string((int)operatorId);
    textures["Idle"] = new Texture(renderer, path + "/Idle.png", false);
    textures["Run"] = new Texture(renderer, path + "/Run.png", false);
}

void Operator::setState(State state) {
    this->numFrames = setNumFrames(state);
    this->stateOperator = state;
}

int Operator::setNumFrames(State state) {
    switch (state) {
        case State::idle:
            return this->textures["Idle"]->frames();
        case State::moving:
            return this->textures["Run"]->frames();
        default:
            return 0;
    }
}

void Operator::render() {
    switch (stateOperator) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures["Idle"]->getTexture());
            break;
        case State::moving:
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

