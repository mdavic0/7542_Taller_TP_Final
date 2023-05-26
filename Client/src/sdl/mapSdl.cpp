#include "mapSdl.h"
#include "common_defines.h"

MapSdl::MapSdl(int id, Renderer& renderer) : mapId(id), renderMap(renderer) {
    this->chargeTexture(renderer);
}

MapSdl::~MapSdl() {
    for (const auto &text : this->textures)
        delete text.second;
}

void MapSdl::render() {
    SDL_Rect rectInit = {0, 0, 1920, 1080};
    SDL_Rect rectFinal = {0, 0, 1024, 768};
    SDL_Texture* textureIdle = textures["sky"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["sun"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["ruins"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["house3"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["house2"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["house1"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["fence"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
    textureIdle = textures["road"]->getTexture();
    this->renderMap.copy(textureIdle, rectInit, rectFinal);
}

void MapSdl::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/maps/" + std::to_string(mapId);
    textures["sky"] = new Texture(renderer, path + "/sky.png", true);
    textures["sun"] = new Texture(renderer, path + "/sun.png", true);
    textures["ruins"] = new Texture(renderer, path + "/ruins.png", true);
    textures["house3"] = new Texture(renderer, path + "/houses3.png", true);
    textures["house2"] = new Texture(renderer, path + "/houses2.png", true);
    textures["house1"] = new Texture(renderer, path + "/houses1.png", true);
    textures["fence"] = new Texture(renderer, path + "/fence.png", true);
    textures["road"] = new Texture(renderer, path + "/road.png", true);
    textures["crater1"] = new Texture(renderer, path + "/crater1.png", true);
    textures["crater2"] = new Texture(renderer, path + "/crater2.png", true);
    textures["crater3"] = new Texture(renderer, path + "/crater3.png", true);
}