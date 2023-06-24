#include "Chunk.h"
#include "SdlException.h"

Chunk::Chunk(const std::string& path) {
    if ((this->chunk = Mix_LoadWAV(path.c_str())) == nullptr)
        throw SdlException("Mix_LoadWav in Chunk");
}

Chunk::~Chunk() {
    if (this->chunk != nullptr)
        Mix_FreeChunk(this->chunk);
}

Chunk::Chunk(Chunk&& other) noexcept : chunk(other.chunk) {
    other.chunk = nullptr;
}

Chunk& Chunk::operator=(Chunk&& other) noexcept {
    if (&other == this)
        return *this;
    if (this->chunk != nullptr)
        Mix_FreeChunk(this->chunk);
    this->chunk = other.chunk;
    other.chunk = nullptr;
    return *this;
}

Mix_Chunk* Chunk::get() const {
    return this->chunk;
}

int Chunk::setVolume(int volume) {
    return Mix_VolumeChunk(this->chunk, volume);
}

int Chunk::getVolume() const {
    return Mix_VolumeChunk(this->chunk, -1);
}
