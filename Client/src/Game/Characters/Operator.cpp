#include "Operator.h"
#include "Defines.h"
#include <iostream>

Operator::Operator(uint8_t id, TypeOperator op, Renderer& renderer,
    WindowSdl& window, ManagerMusic& music) :
    Object(), id(id), operatorId(op), position({0, 0}),
    renderPlayer(renderer), stateOperator(State::idle), numFrames(0),
    flipType(SDL_FLIP_NONE), health(0), animationDeadFinish(false),
    munition(0), window(window), music(music), stopGrenade(false),
    grenadeAvailable(true),
    smokeAvailable(operatorId != TypeOperator::operator_p90 ? true : false) {
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
    int health, uint8_t munition) {
    this->setState(state);
    if (pos.first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (pos.first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = pos;
    this->health = health;
    this->munition = munition;
}

void Operator::update(StOperator snap) {
    this->setState(snap.getState());
    if (snap.getPosition().first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (snap.getPosition().first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = snap.getPosition();
    this->health = snap.getHealth();
    this->munition = snap.getMunition();
    this->grenadeAvailable = snap.isGrenadeAvailable();
    this->smokeAvailable = snap.isSmokeAvailable();
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

int16_t Operator::getPosX() {
    return this->position.first;
}

int16_t Operator::getPosY() {
    return this->position.second;
}

uint8_t Operator::getMunition() {
    return this->munition;
}

bool Operator::isDead() {
    return stateOperator == State::dead; 
}

std::pair<int16_t, int16_t> Operator::getPosition() {
    return this->position;
}

State Operator::getState() {
    return this->stateOperator;
}

bool Operator::getGrenadeAvailable() {
    return this->grenadeAvailable;
}

bool Operator::getSmokeAvailable() {
    return this->smokeAvailable;
}

void Operator::chargeTexture(Renderer& renderer) {
    std::string path = 
                "assets/images/sdl/units/" + std::to_string((int)operatorId);
    textures["Idle"] = std::make_unique<Texture>(renderer, path + "/Idle.png");
    textures["Run"] = std::make_unique<Texture>(renderer, path + "/Run.png");
    textures["Shot"] = std::make_unique<Texture>(renderer,
                                                    path + "/Shot_1.png");
    textures["Hurt"] = std::make_unique<Texture>(renderer, path + "/Hurt.png");
    textures["Recharge"] = std::make_unique<Texture>(renderer,
                                                    path + "/Recharge.png");
    textures["Grenade"] = std::make_unique<Texture>(renderer,
                                                    path + "/Grenade.png");
    textures["Dead"] = std::make_unique<Texture>(renderer, path + "/Dead.png");
    std::string icon = "assets/images/sdl/hud/icon_reviving.png";
    textures["iconHurt"] = std::make_unique<Texture>(renderer, icon);
    std::string bg = "assets/images/sdl/hud/healthbg.png";
    textures["bgIcon"] = std::make_unique<Texture>(renderer, bg);
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
        case State::injure:
            return this->textures["Hurt"]->frames();
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

void Operator::render(SDL_Rect camera) {
    this->renderMusic();
    switch (stateOperator) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures["Idle"]->getTexture(),
                            camera);
            break;
        case State::moving:
            renderAnimation(SPEED_RUN, textures["Run"]->getTexture(), camera);
            break;
        case State::atack:
            renderAnimation(SPEED_ATACK, textures["Shot"]->getTexture(),
                            camera);
            break;
        case State::injure:
            renderIconInjure(camera);
            renderAnimation(SPEED_INJURE, textures["Hurt"]->getTexture(),
                            camera);
            break;
        case State::recharge:
            renderAnimation(SPEED_RECHARGE, textures["Recharge"]->getTexture(),
                            camera);
            break;
        case State::hability:
            if (operatorId != TypeOperator::operator_p90)
                renderGrenade(SPEED_SKILL, textures["Grenade"]->getTexture(),
                            camera);
            else
                renderAnimation(SPEED_SKILL, textures["Grenade"]->getTexture(),
                            camera);
            break;
        case State::stop_hability:
            if (operatorId != TypeOperator::operator_p90)
                renderStopGrenade(SPEED_SKILL, textures["Grenade"]->getTexture(),
                            camera);
            else
                renderAnimation(SPEED_SKILL, textures["Grenade"]->getTexture(),
                            camera);
            break;
        case State::dead:
            renderDead(SPEED_DEAD, textures["Dead"]->getTexture(),camera);
            break;
        default:
            break;
    }
}

void Operator::renderMusic() {
    switch (stateOperator) {
        case State::atack:
            music.playAction(operatorId, "attack");
            break;
        case State::injure:
            music.playAction(operatorId, "injure");
            break;
        case State::recharge:
            music.playAction(operatorId, "recharge");
            break;
        case State::hability:
            music.playAction(operatorId, "grenade");
            break;
        default:
            break;
    }
}

void Operator::renderIconInjure( SDL_Rect camera) {
    SDL_Rect rectInit = { 0, 0, SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  (position.first + SIZE_FRAME / 3) - camera.x,
                            (position.second + SIZE_FRAME / 6) - camera.y,
                            SIZE_FRAME / 3,
                            SIZE_FRAME / 3};
    if (verifyRender(camera, rectFinal)) {
        this->renderPlayer.copy(textures["bgIcon"]->getTexture(), rectInit,
                                rectFinal);
        this->renderPlayer.copy(textures["iconHurt"]->getTexture(), rectInit,
                                rectFinal);
    }
}

void Operator::renderAnimation(int speed, SDL_Texture* texture,
    SDL_Rect camera) {
    int speedAnimation = static_cast<int>((SDL_GetTicks()/speed) % numFrames);
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME, 0,
                            SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (verifyRender(camera, rectFinal))
        this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

void Operator::renderGrenade(int speed, SDL_Texture* texture,
    SDL_Rect camera) {
    int speedAnimation;
    if (!stopGrenade) {
        speedAnimation = static_cast<int>((SDL_GetTicks()/speed) % numFrames);
        if (speedAnimation == 4) {
            stopGrenade = true;
        }
    } else {
        speedAnimation = 4;
    }
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME, 0,
                            SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (verifyRender(camera, rectFinal))
        this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

void Operator::renderStopGrenade(int speed, SDL_Texture* texture,
    SDL_Rect camera) {
    stopGrenade = false;
    std::cout << "solte granada\n";
    int speedAnimation = static_cast<int>((SDL_GetTicks()/speed) % 4) + (numFrames - 4);
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME, 0,
                            SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (verifyRender(camera, rectFinal))
        this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

void Operator::renderDead(int speed, SDL_Texture* texture, SDL_Rect camera) {
    int speedAnimation;
    if (!animationDeadFinish) {
        speedAnimation = static_cast<int>((SDL_GetTicks()/speed) % numFrames);
        if (speedAnimation == (numFrames - 1))
            animationDeadFinish = true;
    } else {
        speedAnimation = numFrames - 1;
    }
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME, 0,
                            SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x, 
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (verifyRender(camera, rectFinal))
        this->renderPlayer.copy(texture, rectInit, rectFinal, this->flipType);
}

bool Operator::verifyRender(SDL_Rect camera, SDL_Rect final) {
    return  position.first >= camera.x - final.w && 
            position.first <= camera.x + window.getWidth() &&
            position.second >= camera.y - final.h &&
            position.second <= camera.y + window.getHeight();
}

Operator::~Operator() {
}

