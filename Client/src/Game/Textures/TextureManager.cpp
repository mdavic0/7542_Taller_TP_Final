#include "TextureManager.h"
#include "Defines.h"
#include "TypeInfected.h"

TextureManager::TextureManager(Renderer& render, uint8_t idMap) : mapTextures({}) {
    loadTextures(render, idMap);
}

void TextureManager::loadTextures(Renderer& render, uint8_t idMap) {
    // Textures Map
    std::string path = PATH_MAPS + std::to_string((int)idMap);
    mapTextures["sky"] = std::make_shared<Texture>(render,
                                                    path + "/sky.png");
    mapTextures["sun"] = std::make_shared<Texture>(render, path + "/sun.png");
    mapTextures["ruins"] = std::make_shared<Texture>(render,
                                                    path + "/ruins.png");
    mapTextures["house3"] = std::make_shared<Texture>(render,
                                                    path + "/houses3.png");
    mapTextures["house2"] = std::make_shared<Texture>(render,
                                                    path + "/houses2.png");
    mapTextures["house1"] = std::make_shared<Texture>(render,
                                                    path + "/houses1.png");
    mapTextures["fence"] = std::make_shared<Texture>(render,
                                                    path + "/fence.png");
    mapTextures["road"] = std::make_shared<Texture>(render,
                                                    path + "/road.png");

    // Texture Obstacles 
    path = PATH_OBSTACLES;
    mapTextures["tire"] = std::make_shared<Texture>(render,
                                                    path + "/tire.png");
    mapTextures["crater"] = std::make_shared<Texture>(render,
                                                    path + "/crater.png");

    // Texture Enemies
    // zombie
    path = PATH_ENEMIES + std::to_string((int)TypeInfected::infected_zombie);
    mapTextures["zombie-Idle"] = std::make_shared<Texture>(render,
                                                    path + "/Idle.png");
    mapTextures["zombie-Run"] = std::make_shared<Texture>(render,
                                                    path + "/Run.png");
    mapTextures["zombie-Attack"] = std::make_shared<Texture>(render,
                                                    path + "/Attack_1.png");
    mapTextures["zombie-Dead"] = std::make_shared<Texture>(render,
                                                    path + "/Dead.png");
    // Jumper
    path = PATH_ENEMIES + std::to_string((int)TypeInfected::infected_jumper);
    mapTextures["jumper-Idle"] = std::make_shared<Texture>(render,
                                                    path + "/Idle.png");
    mapTextures["jumper-Run"] = std::make_shared<Texture>(render,
                                                    path + "/Run.png");
    mapTextures["jumper-Attack"] = std::make_shared<Texture>(render,
                                                    path + "/Attack_1.png");
    mapTextures["jumper-Dead"] = std::make_shared<Texture>(render,
                                                    path + "/Dead.png");
    // witch
    path = PATH_ENEMIES + std::to_string((int)TypeInfected::infected_witch);
    mapTextures["witch-Idle"] = std::make_shared<Texture>(render,
                                                    path + "/Idle.png");
    mapTextures["witch-Run"] = std::make_shared<Texture>(render,
                                                    path + "/Run.png");
    mapTextures["witch-Attack"] = std::make_shared<Texture>(render,
                                                    path + "/Attack_1.png");
    mapTextures["witch-Dead"] = std::make_shared<Texture>(render,
                                                    path + "/Dead.png");
    // spear
    path = PATH_ENEMIES + std::to_string((int)TypeInfected::infected_spear);
    mapTextures["spear-Idle"] = std::make_shared<Texture>(render,
                                                    path + "/Idle.png");
    mapTextures["spear-Run"] = std::make_shared<Texture>(render,
                                                    path + "/Run.png");
    mapTextures["spear-Attack"] = std::make_shared<Texture>(render,
                                                    path + "/Attack_1.png");
    mapTextures["spear-Dead"] = std::make_shared<Texture>(render,
                                                    path + "/Dead.png");
    // venom
    path = PATH_ENEMIES + std::to_string((int)TypeInfected::infected_venom);
    mapTextures["venom-Idle"] = std::make_shared<Texture>(render,
                                                    path + "/Idle.png");
    mapTextures["venom-Run"] = std::make_shared<Texture>(render,
                                                    path + "/Run.png");
    mapTextures["venom-Attack"] = std::make_shared<Texture>(render,
                                                    path + "/Attack_1.png");
    mapTextures["venom-Dead"] = std::make_shared<Texture>(render,
                                                    path + "/Dead.png");
    // Grenade types
    // Explotion
    path = PATH_GRENADES_EXPLOTION;
    mapTextures["grenade"] = std::make_shared<Texture>(render, path);
    // Smoke
    path = PATH_GRENADES_SMOKE;
    mapTextures["smoke"] = std::make_shared<Texture>(render, path);
    // Blitz
    path = PATH_GRENADES_BLITZ;
    mapTextures["blitz"] = std::make_shared<Texture>(render, path);
}

SDL_Texture* TextureManager::getTexture(TypeInfected type,
                                        std::string nameTexture) {
    switch (type) {
        case TypeInfected::infected_zombie:
            return mapTextures["zombie-" + nameTexture]->getTexture(); 
        case TypeInfected::infected_jumper:
            return mapTextures["jumper-" + nameTexture]->getTexture(); 
        case TypeInfected::infected_witch:
            return mapTextures["witch-" + nameTexture]->getTexture(); 
        case TypeInfected::infected_spear:
            return mapTextures["spear-" + nameTexture]->getTexture(); 
        case TypeInfected::infected_venom:
            return mapTextures["venom-" + nameTexture]->getTexture(); 
        default:
            return nullptr;
    }
}

int TextureManager::getFrames(TypeInfected type,
                                        std::string nameTexture) {
    switch (type) {
        case TypeInfected::infected_zombie:
            return mapTextures["zombie-" + nameTexture]->frames(); 
        case TypeInfected::infected_jumper:
            return mapTextures["jumper-" + nameTexture]->frames(); 
        case TypeInfected::infected_witch:
            return mapTextures["witch-" + nameTexture]->frames(); 
        case TypeInfected::infected_spear:
            return mapTextures["spear-" + nameTexture]->frames(); 
        case TypeInfected::infected_venom:
            return mapTextures["venom-" + nameTexture]->frames(); 
        default:
            return 1;
    }
}

int TextureManager::getFrames(TypeGrenade type, std::string nameTexture) {
    switch (type) {
        case TypeGrenade::grenade_explosive:
            return mapTextures["grenade"]->frames();
        case TypeGrenade::grenade_smoke:
            return mapTextures["smoke"]->frames();
        default:
            return 1;
    }
}

int TextureManager::getFramesBlitz() {
    return mapTextures["blitz"]->frames();
}

SDL_Texture* TextureManager::getTexture(std::string nameTexture) {
    return mapTextures[nameTexture]->getTexture();
}

SDL_Texture* TextureManager::getTexture(TypeObstacle type) {
    switch (type) {
        case TypeObstacle::obstacle_tire:
            return mapTextures["tire"]->getTexture();
        case TypeObstacle::obstacle_crater:
            return mapTextures["crater"]->getTexture();
        default:
            return nullptr;
    }
}

TextureManager::~TextureManager() {
}

