#include "GrenadeSdl.h"
#include "Defines.h"
#include <iostream>

GrenadeSdl::GrenadeSdl(GrenadeDto dto, TextureManager& textures,
    Renderer& render, ManagerMusic& music) :
    position(dto.getPosition()), type(dto.getTypeGrenade()),
    explotion(dto.alreadyExploded()), textures(textures), renderer(render),
    numFrames(
        type == TypeGrenade::grenade_explosive ? 
        textures.getFrames(type, "grenade") :
        textures.getFrames(type, "smoke")), finishAnimation(false),
    music(music) {
}

void GrenadeSdl::update(GrenadeDto dto) {
    this->position = dto.getPosition();
    this->explotion = dto.alreadyExploded();
}

void GrenadeSdl::render(SDL_Rect camera) {
    if (!explotion) {
        renderMovement(camera);
    } else {
        renderExplotion(camera);
    }
}

void GrenadeSdl::playEffect() {
    switch (type) {
        case TypeGrenade::grenade_explosive:
            music.playEffectGrenade("explotion");
            break;
        case TypeGrenade::grenade_smoke:
            break;
        default:
            break;
    }
}

void GrenadeSdl::renderExplotion(SDL_Rect camera) {
    int speedAnimation;
    if (!finishAnimation) {
        speedAnimation = static_cast<int>((SDL_GetTicks()/110) % numFrames);
        if (speedAnimation == (numFrames - 1)) {
            finishAnimation = true;
            playEffect();
        }
    }
    SDL_Rect rectInit = {   speedAnimation * SIZE_FRAME, 0,
                            SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (type == TypeGrenade::grenade_explosive){
        this->renderer.copy(textures.getTexture("grenade"), rectInit,
                            rectFinal);
    } else if (type == TypeGrenade::grenade_smoke) {
        this->renderer.copy(textures.getTexture("smoke"), rectInit, rectFinal);
    }
} 

void GrenadeSdl::renderMovement(SDL_Rect camera) {
    SDL_Rect rectInit = {0, 0, SIZE_FRAME, SIZE_FRAME};
    SDL_Rect rectFinal = {  position.first - camera.x,
                            position.second - camera.y,
                            SIZE_FRAME, SIZE_FRAME};
    if (type == TypeGrenade::grenade_explosive){
        this->renderer.copy(textures.getTexture("grenade"), rectInit,
                            rectFinal);
    } else if (type == TypeGrenade::grenade_smoke) {
        this->renderer.copy(textures.getTexture("smoke"), rectInit, rectFinal);
    }
}

std::pair<int16_t, int16_t> GrenadeSdl::getPosition() {
    return this->position;
}

bool GrenadeSdl::exploded() {
    return this->finishAnimation;
} 

TypeGrenade GrenadeSdl::getType() {
    return this->type;
}

GrenadeSdl::~GrenadeSdl() {
}

