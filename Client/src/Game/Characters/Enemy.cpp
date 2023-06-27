#include "Enemy.h"
#include "Defines.h"

Enemy::Enemy(TextureManager& textures, Renderer &render, TypeInfected type,
    WindowSdl& window, ManagerMusic& music) :
    Object(), renderEnemy(render), position({0, 0}), type(type), 
    flipType(SDL_FLIP_NONE), textures(textures), window(window), music(music),
    animationDeadFinish(false) {
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
        case State::dead:
            return this->textures.getFrames(type, "Dead");
        case State::injure:
            return this->textures.getFrames(type, "Hurt");
        default:
            return 1;
    }
}

void Enemy::render(SDL_Rect camera) {
    switch (stateEnemy) {
        case State::idle:
            renderAnimation(SPEED_IDLE, textures.getTexture(type, "Idle"),
                            camera);
            // if (type == TypeInfected::infected_zombie ||
            //     type == TypeInfected::infected_witch ||
            //     type == TypeInfected::infected_spear)
            //     music.playAction(type, "idle");
            break;
        case State::moving:
            renderAnimation(SPEED_RUN, textures.getTexture(type, "Run"),
                            camera);
            break;
        case State::atack:
            renderAnimation(SPEED_ATACK, textures.getTexture(type, "Attack"),
                            camera);
            music.playAction(type, "attack");
            break;
        case State::dead:
            music.playAction(type, "dead");
            renderDead(SPEED_DEAD, textures.getTexture(type, "Dead"), camera);
            break;
        case State::injure:
            renderAnimation(SPEED_INJURE, textures.getTexture(type, "Hurt"),
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
                        SIZE_FRAME_ENEMY, SIZE_FRAME_ENEMY};
    } else if (type == TypeInfected::infected_spear ||
                type == TypeInfected::infected_venom) {
        rectInit = {   (speedAnimation * (SIZE_FRAME)), 0,
                                SIZE_FRAME, SIZE_FRAME};
        rectFinal = {   position.first - camera.x,
                        position.second - camera.y,
                        SIZE_FRAME, SIZE_FRAME};
    }
    if (verifyRender(camera, rectFinal))
        this->renderEnemy.copy(texture, rectInit, rectFinal, this->flipType);
}

void Enemy::renderDead(int speed, SDL_Texture* texture, SDL_Rect camera) {
    int speedAnimation;
    if (!animationDeadFinish) {
        speedAnimation = static_cast<int>((SDL_GetTicks()/speed) % numFrames);
        if (speedAnimation == (numFrames - 1))
            animationDeadFinish = true;
    } else {
        speedAnimation = numFrames - 1;
    }
    SDL_Rect rectInit;
    SDL_Rect rectFinal;
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
    if (verifyRender(camera, rectFinal))
        this->renderEnemy.copy(texture, rectInit, rectFinal, this->flipType);
}

bool Enemy::verifyRender(SDL_Rect camera, SDL_Rect final) {
    return  position.first >= camera.x - final.w && 
            position.first <= camera.x + window.getWidth() &&
            position.second >= camera.y - final.h &&
            position.second <= camera.y + window.getHeight();
}

bool Enemy::isDeadFinish() {
    return this->animationDeadFinish;
}

Enemy::~Enemy() {
}
