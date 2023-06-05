#ifndef FONTSDL_H_
#define FONTSDL_H_

#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_surface.h>
#include <string>

class Font {
    private:
        TTF_Font* font;
    public:
        Font(const std::string& file, int size);
        ~Font();
        Font(const Font&) = delete;
        Font& operator=(const Font& other) = delete;
        Font(Font &&other) noexcept;
        Font& operator=(Font&& other) noexcept;
        SDL_Surface* RenderText_Solid(std::string text, SDL_Color fg);
        void setHinting();
        void getSizeFont(const std::string& text, int* textW, int* textH);
};

#endif
