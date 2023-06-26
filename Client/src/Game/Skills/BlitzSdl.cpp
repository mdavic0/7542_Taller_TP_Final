#include "BlitzSdl.h"
#include "Defines.h"

BlitzSdl::BlitzSdl(Renderer& render, TextureManager& textures,
    ManagerMusic& music, WindowSdl& window) : renderer(render),
    textures(textures), music(music), window(window),
    numFrames(textures.getFramesBlitz()) {
}

void BlitzSdl::render(SDL_Rect camera) {
    int repet = window.getWidth() / SIZE_FRAME;
    uint32_t lastSoundTime = 0;
    for (int i = 0; i < repet; ++i ) {
        this->renderExplotion(i, camera);
    }
    uint32_t currentTime = SDL_GetTicks();
    if (currentTime - lastSoundTime >= 4000) {
        // music.playEffectGrenade("explotion");
        lastSoundTime = currentTime;
    }
}

void BlitzSdl::renderExplotion(int i, SDL_Rect camera) {
    speedAnimation = static_cast<int>((SDL_GetTicks()/100) % numFrames);
    if (speedAnimation != numFrames - 1) {
        SDL_Rect rectInit =  {  SIZE_FRAME * speedAnimation, 0,
                                SIZE_FRAME, SIZE_FRAME};
        SDL_Rect rectFinal = {  i * (SIZE_FRAME + 2),
                                window.getHeight() - camera.y,
                                SIZE_FRAME, SIZE_FRAME};
        this->renderer.copy(textures.getTexture("blitz"), rectInit, rectFinal);
    }
}

BlitzSdl::~BlitzSdl() {
}

