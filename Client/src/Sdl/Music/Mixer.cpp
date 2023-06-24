#include "Mixer.h"
#include "SdlException.h"

Mixer::Mixer(int frequency, uint16_t format, int channels, int chunkSize) :
    open(true) {
    if (Mix_OpenAudio(frequency, format, channels, chunkSize) != 0)
        throw SdlException("Mix_OpenAudio");
}

Mixer::~Mixer() {
    if (open)
        Mix_CloseAudio();
}

Mixer::Mixer(Mixer&& other) noexcept : open(other.open) {
    other.open = false;
}

Mixer& Mixer::operator=(Mixer&& other) noexcept {
    if (&other == this)
        return *this;
    if (open)
        Mix_CloseAudio();
    open = other.open;
    other.open = false;
    return *this;
}

int Mixer::playChannel(int channel, Mix_Chunk* chunk, int loops) {
    int chan;
    if ((chan = Mix_PlayChannel(channel, chunk, loops)) == -1)
        throw SdlException("Mix_PlayChannel");
    return chan;
}

void Mixer::haltChannel(int channel) {
    Mix_HaltChannel(channel);
}

int Mixer::setVolume(int channel, int volume) {
    return Mix_Volume(channel, volume);
}
