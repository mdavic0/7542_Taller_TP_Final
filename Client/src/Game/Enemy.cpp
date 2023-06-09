#include "Enemy.h"
#include "Defines.h"

Enemy::Enemy(Renderer &render, uint8_t type) : renderEnemy(render), health(0),
    position({0, 0}), type(type), flipType(SDL_FLIP_NONE) {
    this->chargeTextures();
}

void Enemy::chargeTextures() {
    std::string path = 
                    "assets/images/sdl/enemys/" + std::to_string((int)type);
    textures["Idle"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Idle.png", false);
    textures["Run"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Run.png", false);
    textures["Attack"] = std::make_unique<Texture>(renderEnemy,
                                                path + "/Attack_1.png", false);
}

void Enemy::update(std::pair<int16_t, int16_t> pos, State state,
                    int health) {
    this->setState(state);
    if (pos.first < position.first)
        this->flipType = SDL_FLIP_HORIZONTAL;
    else if (pos.first > position.first)
        this->flipType = SDL_FLIP_NONE;
    this->position = pos;
    this->health = health;
}

void Enemy::setState(State state) {
    this->numFrames = setNumFrames(state);
    this->stateEnemy = state;
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

void Enemy::render() {
    switch (stateEnemy) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures["Idle"]->getTexture());
            break;
        case State::moving:
            renderAnimation(SPEED_RUN, textures["Run"]->getTexture());
            break;
        case State::atack:
            renderAnimation(100, textures["Attack"]->getTexture());
            break;
        default:
            break;
    }
}

void Enemy::renderAnimation(int speed, SDL_Texture* texture) {
    int speedAnimation = static_cast<int>((SDL_GetTicks() / speed) % numFrames);
    SDL_Rect rectInit, rectFinal;
    if (type == 0 || type == 1 || type == 2) {
        rectInit = {   (speedAnimation * (SIZE_FRAME_ENEMY)), 0,
                                SIZE_FRAME_ENEMY, SIZE_FRAME_ENEMY};
        rectFinal = {  position.first, position.second,
                                SIZE_FRAME_ENEMY, SIZE_FRAME_ENEMY};
    } else if (type == 3 || type == 4 ) {
        rectInit = {   (speedAnimation * (SIZE_FRAME)), 0,
                                SIZE_FRAME, SIZE_FRAME};
        rectFinal = {  position.first, position.second,
                                SIZE_FRAME, SIZE_FRAME};
    }
    this->renderEnemy.copy(texture, rectInit, rectFinal, this->flipType);
}

Enemy::~Enemy() {
}
