#include "Hud.h"

Hud::Hud(TypeOperator type, Renderer& render) : type(type), renderHud(render) {
    this->loadTextures();
}

void Hud::loadTextures() {
    std::string path = "assets/images/sdl/hud/";
    SDL_Color c = {0, 0, 0, 255};
    texturesHud["healthbg1"] = new Texture(renderHud, path + "healthbg_1.png", c);
    texturesHud["healthbg2"] = new Texture(renderHud, path + "healthbg_2.png", c);
    texturesHud["healthbg3"] = new Texture(renderHud, path + "healthbg_3.png", c);
    texturesHud["healthbg4"] = new Texture(renderHud, path + "healthbg_4.png", c);
    texturesHud["bar-bg"] = new Texture(renderHud, path + "bar_bg.png", false);
    texturesHud["bar-fill"] = new Texture(renderHud, path + "bar_fill.png", false);
}

void Hud::render() {
    this->renderBg();
    this->renderHealthBar();
}

void Hud::renderBg() {
    SDL_Rect rectInit = {   0,
                            0,
                            512,
                            256};
    SDL_Rect rectFinal = {  0,
                            0,
                            512 * 6/5,
                            256 * 7/10};
    this->renderHud.copy(texturesHud["healthbg1"]->getTexture(), rectInit, rectFinal);
    this->renderHud.copy(texturesHud["healthbg2"]->getTexture(), rectInit, rectFinal);
    this->renderHud.copy(texturesHud["healthbg3"]->getTexture(), rectInit, rectFinal);
    this->renderHud.copy(texturesHud["healthbg4"]->getTexture(), rectInit, rectFinal);
}

void Hud::renderHealthBar() {
    SDL_Rect rectInit = {   0,
                            0,
                            512,
                            128};
    SDL_Rect rectFinal = {  30,
                            35,
                            512 * 6/10,
                            128 * 7/10};
    this->renderHud.copy(texturesHud["bar-bg"]->getTexture(), rectInit, rectFinal);
}

Hud::~Hud() {
    for (auto &texture : texturesHud)
        delete texture.second;
}

