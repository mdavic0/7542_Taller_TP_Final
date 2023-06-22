#include "Enemy.h"
#include "Defines.h"

Enemy::Enemy(TextureManager& textures, Renderer &render, TypeInfected type) :
    renderEnemy(render), position({0, 0}), type(type), 
    flipType(SDL_FLIP_NONE), textures(textures) {
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
            return this->textures.getFrames(type, "Idle");
        case State::moving:
            return this->textures.getFrames(type, "Run");
        case State::atack:
            return this->textures.getFrames(type, "Attack");
        default:
            return 0;
    }
}

void Enemy::render(SDL_Rect camera) {
    switch (stateEnemy) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures.getTexture(type, "Idle"),
                            camera);
            break;
        case State::moving:
            renderAnimation(SPEED_RUN, textures.getTexture(type, "Run"),
                            camera);
            break;
        case State::atack:
            renderAnimation(SPEED_ATACK, textures.getTexture(type, "Attack"),
                            camera);
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
                        SIZE_FRAME, SIZE_FRAME};
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
