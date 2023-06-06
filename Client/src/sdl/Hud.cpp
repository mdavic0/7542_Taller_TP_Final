#include "Hud.h"

Hud::Hud(TypeOperator type, Renderer& render) : type(type), renderHud(render) {
    this->loadTextures();
}

void Hud::loadTextures() {
    std::string path = "assets/images/sdl/hud/";
    texturesHud["bar-bg"] = new Texture(renderHud, path, false);
}

Hud::~Hud() {
    for (auto &texture : texturesHud)
        delete texture.second;
}

