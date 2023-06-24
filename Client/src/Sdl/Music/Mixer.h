#ifndef MIXERSDL_H_
#define MIXERSDL_H_

#include <SDL2/SDL_mixer.h>

class Mixer {
    private:
        bool open;
    public:
        Mixer(int frequency, uint16_t format, int channels,
                    int chunkSize);
        ~Mixer();
        Mixer(Mixer&& other) noexcept;
        Mixer& operator=(Mixer&& other) noexcept;
        Mixer(const Mixer& other) = delete;
        Mixer& operator=(const Mixer& other) = delete;

        void haltChannel(int channel = -1);
        int playChannel(int channel, Mix_Chunk* chunk, int loops = 0);
        int setVolume(int channel, int volume);
};

#endif
