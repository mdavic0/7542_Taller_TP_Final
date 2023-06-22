#include "mapSdl.h"
#include "Defines.h"

MapSdl::MapSdl(TextureManager& textureManager, Renderer& render,
    WindowSdl& window) : textures(textureManager), renderMap(render),
    window(window) {
}

MapSdl::~MapSdl() {
}

void MapSdl::render(SDL_Rect camera) {

    SDL_Rect rectInit =  {0, 0, camera.w, camera.h};
    SDL_Rect rectFinal = {0, 0, window.getWidth(), window.getHeight()};
    this->renderMap.copy(textures.getTexture("sky"), rectInit, rectFinal);
    this->renderMap.copy(textures.getTexture("sun"), rectInit, rectFinal); 

    int offsetX = camera.x % window.getWidth(); 
    int repet = MAP_WIDTH / SIZE_SPRITE_MAP_X;
    for (int i = 0; i < repet; ++i ) {
        int xPos = i * window.getWidth() - offsetX;
        rectFinal.x = xPos;
        this->renderMap.copy(textures.getTexture("ruins"), rectInit, rectFinal);
        this->renderMap.copy(textures.getTexture("house3"), rectInit, rectFinal);
        this->renderMap.copy(textures.getTexture("house2"), rectInit, rectFinal);
        this->renderMap.copy(textures.getTexture("house1"), rectInit, rectFinal);
        this->renderMap.copy(textures.getTexture("fence"), rectInit, rectFinal);
        this->renderMap.copy(textures.getTexture("road"), rectInit, rectFinal);
    }
}
