#include "ManagerMusic.h"
#include "SdlException.h"
#include "Defines.h"

ManagerMusic::ManagerMusic() : 
    mixer(MIX_DEFAULT_FREQUENCY, AUDIO_S16, MIX_DEFAULT_CHANNELS, 512) {
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
    listMusic["idf-recharge"] = std::make_unique<Chunk>(path + "/recharge.wav");
    listMusic["idf-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["idf-grenade"] = std::make_unique<Chunk>(path + "/grenade.wav");
    listMusic["idf-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    // P90 operator
    path = PATH_MUSIC_OPERATOR +
                        std::to_string((int)TypeOperator::operator_p90);
    listMusic["p90-recharge"] = std::make_unique<Chunk>(path + "/recharge.wav");
    listMusic["p90-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["p90-grenade"] = std::make_unique<Chunk>(path + "/grenade.wav");
    listMusic["p90-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
    // Scout operator
    path = PATH_MUSIC_OPERATOR +
                        std::to_string((int)TypeOperator::operator_scout);
    listMusic["scout-recharge"] = std::make_unique<Chunk>(path + "/recharge.wav");
    listMusic["scout-injure"] = std::make_unique<Chunk>(path + "/injure.wav");
    listMusic["scout-grenade"] = std::make_unique<Chunk>(path + "/grenade.wav");
    listMusic["scout-attack"] = std::make_unique<Chunk>(path + "/attack.wav");
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
            playEffect(listMusic["scout-" + action]->get());
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

