#include "BlitzSdl.h"
#include "Defines.h"

BlitzSdl::BlitzSdl(Renderer& render, TextureManager& textures,
    ManagerMusic& music, WindowSdl& window) : renderer(render),
    textures(textures), music(music), window(window),
    numFrames(textures.getFramesBlitz()) {
}

void BlitzSdl::render(SDL_Rect camera) {
    int repet = WIDTH_SCREEN_INIT / SIZE_FRAME;
    for (int i = 1; i < repet - 1; ++i ) {
        this->renderExplotion(i, camera);
    }
    music.playEffectGrenade("explotion");
}

void BlitzSdl::renderExplotion(int i, SDL_Rect camera) {
    speedAnimation = static_cast<int>((SDL_GetTicks()/100) % numFrames);
    if (speedAnimation != numFrames - 1) {
        SDL_Rect rectInit =  {  SIZE_FRAME * speedAnimation, 0,
                                SIZE_FRAME, SIZE_FRAME};
        SDL_Rect rectFinal = {  i * (SIZE_FRAME),
                                800,
                                SIZE_FRAME, SIZE_FRAME};
        this->renderer.copy(textures.getTexture("blitz"), rectInit, rectFinal);
    }
}

BlitzSdl::~BlitzSdl() {
}

