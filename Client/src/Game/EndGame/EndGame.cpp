#include "EndGame.h"
#include "Defines.h"
#include <SDL2/SDL.h>

EndGame::EndGame(Font& font, Renderer& renderer, TextureManager& textures,
    TypeGame type, WindowSdl& window) : font(font), renderer(renderer), 
    textures(textures), type(type), window(window) {
}

EndGame::~EndGame() {
}

void EndGame::render() {
    if (type == TypeGame::game_clear_zone)
        renderClearZone();
    else if (type == TypeGame::game_survival)
        renderSurvival();
}

void EndGame::renderClearZone() {
    SDL_Color color = COLOR_WHITE;
    int w, h;
    font.getSizeFont(TEXT_CLEAR_ZONE, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_CLEAR_ZONE,
                                                        color));
    SDL_Rect final = {  (window.getWidth() - w) / 2,
                        (window.getHeight() - h) / 2,
                        w, h};
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { (window.getWidth() - rectFinal.w) / 2, 
                            (window.getHeight() - rectFinal.h) / 2,
                            SPRITE_BG_W * 15 / 10, SPRITE_BG_H};
    this->renderer.copy(textures.getTexture("healthbg"), rectInit,
                        rectFinal);
    this->renderer.copyFont(textureFont.getTexture(), final);
}

void EndGame::renderSurvival() {
    SDL_Color color = COLOR_WHITE;
    int w, h;
    font.getSizeFont(TEXT_SURVIVAL, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_SURVIVAL,
                                                        color));
    SDL_Rect final = {  (window.getWidth() - w) / 2,
                        (window.getHeight() - h) / 2,
                        w, h};
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { (window.getWidth() -  rectFinal.w) / 2, 
                            (window.getHeight() - rectFinal.h) / 2,
                            SPRITE_BG_W * 15 / 10, SPRITE_BG_H};
    this->renderer.copy(textures.getTexture("healthbg"), rectInit,
                        rectFinal);
    this->renderer.copyFont(textureFont.getTexture(), final);
}
