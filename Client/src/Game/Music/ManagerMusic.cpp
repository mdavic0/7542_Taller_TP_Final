#include "ManagerMusic.h"
#include "SdlException.h"
#include "Defines.h"
#include <SDL2/SDL.h>

ManagerMusic::ManagerMusic() : 
    mixer(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512),
    lastSoundTime(0) {
    this->loadMusic();
}

void ManagerMusic::loadMusic() {
    // Music
    std::string path = PATH_MUSIC_LOBBY;
    listMusic["lobby"] = std::make_unique<Chunk>(path);
    path = PATH_MUSIC_GAME;
    listMusic["game"] = std::make_unique<Chunk>(path);
    // Idf Operator
    path = PATH_MUSIC_OPERATOR +
            std::to_string((int)TypeOperator::operator_idf);
    listMusic["idf-recharge"] = std::make_unique<Chunk>(path +
                                                        "/recharge.wav");
    listMusic["idf-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["idf-grenade"] = std::make_unique<Chunk>(path + "/grenade.wav");
    listMusic["idf-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    // P90 operator
    path = PATH_MUSIC_OPERATOR +
                        std::to_string((int)TypeOperator::operator_p90);
    listMusic["p90-recharge"] = std::make_unique<Chunk>(path +
                                                        "/recharge.wav");
    listMusic["p90-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["p90-grenade"] = std::make_unique<Chunk>(path + "/grenade.wav");
    listMusic["p90-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    // Scout operator
    path = PATH_MUSIC_OPERATOR +
                        std::to_string((int)TypeOperator::operator_scout);
    listMusic["scout-recharge"] = std::make_unique<Chunk>(path +
                                                        "/recharge.wav");
    listMusic["scout-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["scout-grenade"] = std::make_unique<Chunk>(path +
                                                        "/grenade.wav");
    listMusic["scout-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    // Zombie infected
    path = PATH_MUSIC_ENEMY +
            std::to_string((int)TypeInfected::infected_zombie);
    listMusic["zombie-idle"] = std::make_unique<Chunk>(path + "/idle.wav");
    listMusic["zombie-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    listMusic["zombie-dead"] = std::make_unique<Chunk>(path + "/dead.wav");
    // Jumper infected
    path = PATH_MUSIC_ENEMY +
            std::to_string((int)TypeInfected::infected_jumper);
    listMusic["jumper-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    listMusic["jumper-dead"] = std::make_unique<Chunk>(path + "/dead.wav");
    // Witch infected
    path = PATH_MUSIC_ENEMY +
            std::to_string((int)TypeInfected::infected_witch);
    listMusic["witch-idle"] = std::make_unique<Chunk>(path + "/idle.wav");
    listMusic["witch-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    listMusic["witch-dead"] = std::make_unique<Chunk>(path + "/dead.wav");
    // spear infected
    path = PATH_MUSIC_ENEMY +
            std::to_string((int)TypeInfected::infected_spear);
    listMusic["spear-idle"] = std::make_unique<Chunk>(path + "/idle.wav");
    listMusic["spear-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    listMusic["spear-dead"] = std::make_unique<Chunk>(path + "/dead.wav");
    // Venom infected
    path = PATH_MUSIC_ENEMY +
            std::to_string((int)TypeInfected::infected_spear);
    listMusic["venom-idle"] = std::make_unique<Chunk>(path + "/idle.wav");
    listMusic["venom-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    listMusic["venom-dead"] = std::make_unique<Chunk>(path + "/dead.wav");
}

void ManagerMusic::playAction(TypeOperator type, const std::string& action) {
    switch (type) {
        case TypeOperator::operator_idf:
            playEffect(listMusic["idf-" + action]->get());
            break;
        case TypeOperator::operator_p90:
            playEffect(listMusic["p90-" + action]->get());
            break;
        case TypeOperator::operator_scout:
            if (action == "attack") {
                uint32_t currentTime = SDL_GetTicks();
                if (currentTime - lastSoundTime >= 400) {
                    playEffect(listMusic["scout-" + action]->get());
                    lastSoundTime = currentTime;
                }
            } else {
                playEffect(listMusic["scout-" + action]->get());
            }
            break;
        default:
            break;
    }
}

void ManagerMusic::playAction(TypeInfected type, const std::string& action) {
    if (action !=  "attack") {
        this->playInfectedMusic(type, action);
    } else {
        uint32_t currentTime = SDL_GetTicks();
        if (currentTime - lastSoundTime >= 100) {
            this->playInfectedMusic(type, action);
            lastSoundTime = currentTime;
        }
    }
}

void ManagerMusic::playInfectedMusic(TypeInfected type, const std::string& action) {
    switch (type) {
        case TypeInfected::infected_zombie:
            playEffect(listMusic["zombie-" + action]->get());
            break;
        case TypeInfected::infected_jumper:
            playEffect(listMusic["jumper-" + action]->get());
            break;
        case TypeInfected::infected_witch:
            playEffect(listMusic["witch-" + action]->get());
            break;
        case TypeInfected::infected_spear:
            playEffect(listMusic["spear-" + action]->get());
            break;
        case TypeInfected::infected_venom:
            playEffect(listMusic["venom-" + action]->get());
            break;
        default:
            break;
    }
}


void ManagerMusic::playEffect(Mix_Chunk* chunk) {
    this->mixer.playChannel(2, chunk, 0);
}

void ManagerMusic::playMusic(std::string music) {
    this->mixer.haltChannel(1);
    this->mixer.setVolume(1, 15);
    this->mixer.playChannel(1, listMusic[music]->get(), -1);
}

ManagerMusic::~ManagerMusic() {
}

