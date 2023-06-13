#include "Operator.h"
#include "Defines.h"
#include <iostream>

Operator::Operator(uint8_t id, TypeOperator op, Renderer& renderer) : id(id),
    operatorId(op), position({0, 0}), renderPlayer(renderer),
    stateOperator(State::idle), numFrames(0), flipType(SDL_FLIP_NONE),
    health(0), animationDeadFinish(false) {
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

void Operator::update(std::pair<int16_t, int16_t> pos, State state,
    int health) {
    this->setState(state);
    if (pos.first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (pos.first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = pos;
    this->health = health;
}

TypeOperator Operator::getType() {
    return this->operatorId;
}

uint8_t Operator::getId() {
    return this->id;
}

uint8_t Operator::getHealth() {
    return this->health;
}

int16_t Operator::getPosY() {
    return this->position.second;
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = 
                "assets/images/sdl/units/" + std::to_string((int)operatorId);
    textures["Idle"] = std::make_unique<Texture>(renderer,
                                                path + "/Idle.png", false);
    textures["Run"] = std::make_unique<Texture>(renderer,
                                                path + "/Run.png", false);
    textures["Shot"] = std::make_unique<Texture>(renderer,
                                                path + "/Shot_1.png", false);
    textures["Recharge"] = std::make_unique<Texture>(renderer,
                                                path + "/Recharge.png", false);
    textures["Grenade"] = std::make_unique<Texture>(renderer,
                                                path + "/Grenade.png", false);
    textures["Dead"] = std::make_unique<Texture>(renderer,
                                                path + "/Dead.png", false);
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
        case State::atack:
            return this->textures["Shot"]->frames();
        case State::recharge:
            return this->textures["Recharge"]->frames();
        case State::hability:
            return this->textures["Grenade"]->frames();
        case State::dead:
            return this->textures["Dead"]->frames();
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
        case State::atack:
            renderAnimation(100, textures["Shot"]->getTexture());
            break;
        case State::recharge:
            renderAnimation(100, textures["Recharge"]->getTexture());
            break;
        case State::hability:
            renderAnimation(100, textures["Grenade"]->getTexture());
            break;
        case State::dead:
            renderDead(100, textures["Dead"]->getTexture());
            break;
        default:
            break;
    }
}

void Operator::renderAnimation(int speed, SDL_Texture* texture) {
    int speedAnimation = static_cast<int>((SDL_GetTicks() / speed) % numFrames);
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME,
                            0,
                            SIZE_FRAME,
                            SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first,
                            position.second,
                            SIZE_FRAME,
                            SIZE_FRAME};
    this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

void Operator::renderDead(int speed, SDL_Texture* texture) {
    int speedAnimation;
    if (!animationDeadFinish) {
        speedAnimation = static_cast<int>((SDL_GetTicks() / speed) % numFrames);
        if (speedAnimation == (numFrames - 1))
            animationDeadFinish = true;
    } else {
        speedAnimation = numFrames - 1;
    }
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME,
                            0,
                            SIZE_FRAME,
                            SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first,
                            position.second,
                            SIZE_FRAME,
                            SIZE_FRAME};
    this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

Operator::~Operator() {
}

