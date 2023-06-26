#ifndef MANAGER_MUSIC_H_
#define MANAGER_MUSIC_H_

#include <map>
#include <memory>
#include <SDL2/SDL_mixer.h>
#include <string>
#include "Chunk.h"
#include "Mixer.h"
#include "TypeOperator.h"
#include "TypeInfected.h"

class ManagerMusic {
    private:
        Mixer mixer;
        std::map<std::string, std::unique_ptr<Chunk>> listMusic;
        uint32_t lastSoundTime;
        void loadMusic();
        void playEffectOperator(Mix_Chunk* chunk);
        void playEffectEnemy(Mix_Chunk* chunk);
        void playInfectedMusic(TypeInfected type, const std::string& action);
    public:
        ManagerMusic();
        ~ManagerMusic();
        void playAction(TypeOperator type, const std::string& action);
        void playAction(TypeInfected type, const std::string& action);
        void playMusic(std::string music);
        void playEffectGrenade(std::string music);

};

#endif
