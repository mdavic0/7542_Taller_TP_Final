#include "Enemy.h"
#include "Defines.h"

Enemy::Enemy(Renderer &render, TypeInfected type) : renderEnemy(render),
    position({0, 0}), type(type), flipType(SDL_FLIP_NONE) {
    this->chargeTextures();
}

void Enemy::chargeTextures() {
    std::string path = 
                    "assets/images/sdl/enemys/" + std::to_string((int)type);
    textures["Idle"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Idle.png");
    textures["Run"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Run.png");
    textures["Attack"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Attack_1.png");
}

void Enemy::update(std::pair<int16_t, int16_t> pos, State state) {
    this->setState(state);
    if (pos.first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (pos.first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = pos;
}

void Enemy::setState(State state) {
    this->numFrames = setNumFrames(state);
    this->stateEnemy = state;
}

int16_t Enemy::getPosY() {
    return this->position.second;
}

int Enemy::setNumFrames(State state) {
    switch (state) {
        case State::idle:
            return this->textures["Idle"]->frames();
        case State::moving:
            return this->textures["Run"]->frames();
        case State::atack:
            return this->textures["Attack"]->frames();
        default:
            return 0;
    }
}

void Enemy::render(SDL_Rect camera) {
    switch (stateEnemy) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures["Idle"]->getTexture(), camera);
            break;
        case State::moving:
            renderAnimation(SPEED_RUN, textures["Run"]->getTexture(), camera);
            break;
        case State::atack:
            renderAnimation(100, textures["Attack"]->getTexture(), camera);
            break;
        default:
            break;
    }
}

void Enemy::renderAnimation(int speed, SDL_Texture* texture, SDL_Rect camera) {
    int speedAnimation = static_cast<int>((SDL_GetTicks() / speed) % numFrames);
    SDL_Rect rectInit, rectFinal;
    if (type == TypeInfected::infected_zombie ||
        type == TypeInfected::infected_jumper ||
        type == TypeInfected::infected_witch) {
        rectInit = {   (speedAnimation * (SIZE_FRAME_ENEMY)), 0,
                                SIZE_FRAME_ENEMY, SIZE_FRAME_ENEMY};
        rectFinal = {   position.first - camera.x,
                        position.second - camera.y,
                        SIZE_FRAME_ENEMY, SIZE_FRAME_ENEMY};
    } else if (type == TypeInfected::infected_spear ||
                type == TypeInfected::infected_venom) {
        rectInit = {   (speedAnimation * (SIZE_FRAME)), 0,
                                SIZE_FRAME, SIZE_FRAME};
        rectFinal = {   position.first - camera.x,
                        position.second - camera.y,
                        SIZE_FRAME, SIZE_FRAME};
    }
    this->renderEnemy.copy(texture, rectInit, rectFinal, this->flipType);
}

Enemy::~Enemy() {
}
