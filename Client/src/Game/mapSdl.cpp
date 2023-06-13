#include "mapSdl.h"
#include "Defines.h"

MapSdl::MapSdl(uint8_t id, Renderer& renderer, WindowSdl& window) : mapId(id),
    renderMap(renderer), windowMap(window), textures({}) {
    this->chargeTexture(renderer);
}

MapSdl::~MapSdl() {
}

void MapSdl::render(SDL_Rect camera) {
    SDL_Rect rectInit = camera;
    SDL_Rect rectFinal = {0,0, windowMap.getWidth(), windowMap.getHeight()};
    this->renderMap.copy(textures["sky"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["sun"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["ruins"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["house3"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["house2"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["house1"]->getTexture(), rectInit, rectFinal);
    this->renderMap.copy(textures["fence"]->getTexture(), rectInit,rectFinal);
    this->renderMap.copy(textures["road"]->getTexture(), rectInit, rectFinal);
}

void MapSdl::chargeTexture(Renderer& renderer) {
    std::string path = "assets/images/sdl/maps/" + std::to_string((int)mapId);
    textures["sky"] = std::make_unique<Texture>(renderer, path + "/sky.png");
    textures["sun"] = std::make_unique<Texture>(renderer, path + "/sun.png");
    textures["ruins"] = std::make_unique<Texture>(renderer, path + "/ruins.png");
    textures["house3"] = std::make_unique<Texture>(renderer, path + "/houses3.png");
    textures["house2"] = std::make_unique<Texture>(renderer, path + "/houses2.png");
    textures["house1"] = std::make_unique<Texture>(renderer, path + "/houses1.png");
    textures["fence"] = std::make_unique<Texture>(renderer, path + "/fence.png");
    textures["road"] = std::make_unique<Texture>(renderer, path + "/road.png");
    // textures["crater1"] = new Texture(renderer, path + "/crater1.png", true);
    // textures["crater2"] = new Texture(renderer, path + "/crater2.png", true);
    // textures["crater3"] = new Texture(renderer, path + "/crater3.png", true);
}