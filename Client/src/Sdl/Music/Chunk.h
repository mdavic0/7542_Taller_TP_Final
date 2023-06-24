#ifndef CHUNK_SDL_H_
#define CHUNK_SDL_H_

#include <SDL2/SDL_mixer.h>
#include <string>

class Chunk {
    private:
        Mix_Chunk* chunk;
    public:
        explicit Chunk(const std::string& path);
        ~Chunk();
        Chunk(Chunk&& other) noexcept;
        Chunk& operator=(Chunk&& other) noexcept;
        Chunk(const Chunk& other) = delete;
        Chunk& operator=(const Chunk& other) = delete;
        Mix_Chunk* get() const;
        int setVolume(int Volume);
        int getVolume() const;
};

#endif
