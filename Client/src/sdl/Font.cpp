#include "Font.h"
#include "SdlException.h"

Font::Font(const std::string& file, int size) {
    this->font = TTF_OpenFontIndex(file.c_str(), size, 0);
    if (this->font == nullptr)
        throw SdlException("Failed to open Font");
}

Font::~Font() {
    if (this->font != nullptr)
        TTF_CloseFont(this->font);
}

SDL_Surface* Font::RenderText_Solid(std::string text, SDL_Color fg) {
    SDL_Surface* surface = TTF_RenderText_Solid(this->font, text.c_str(), fg);
    if (surface == nullptr)
        throw SdlException("Failed create Surface");
    return surface;
}

void Font::setHinting() {
    TTF_SetFontHinting(this->font, TTF_HINTING_NORMAL);
}

void Font::getSizeFont(const std::string& text, int* textW, int* textH) {
    if (TTF_SizeText(this->font, text.c_str(), textW, textH) != 0)
        throw SdlException("Failed get size font");
}

Font::Font(Font&& other) noexcept : font(other.font) {
    other.font = nullptr;
}

Font& Font::operator=(Font&& other) noexcept {
    if (&other == this)
        return *this;
    if (this->font != nullptr)
        TTF_CloseFont(this->font);
    this->font = other.font;
    other.font = nullptr;
    return *this;
}
