#include "EndGame.h"
#include "Defines.h"
#include <SDL2/SDL.h>

EndGame::EndGame(Font& font, Renderer& renderer, TextureManager& textures,
    TypeGame type, WindowSdl& window) : font(font), renderer(renderer), 
    textures(textures), type(type), window(window), stats() {
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
    int w, h, w2, h2;
    font.getSizeFont(TEXT_CLEAR_ZONE, &w, &h);
    font.getSizeFont(TEXT_END_GAME, &w2, &h2);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_CLEAR_ZONE,
                                                        color));
    Texture textureFont2(renderer, font.RenderText_Solid(TEXT_END_GAME,
                                                        color));
    SDL_Rect final = {  650, 430, w, h};
    SDL_Rect final2 = { 600, final.y + h2 + 10, w2, h2};
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { 574, 375, SPRITE_BG_W, SPRITE_BG_H};
    window.adjustedRect(final);
    window.adjustedRect(final2);
    window.adjustedRect(rectFinal);
    this->renderer.copy(textures.getTexture("healthbg"), rectInit,
                        rectFinal);
    this->renderer.copyFont(textureFont.getTexture(), final);
    this->renderer.copyFont(textureFont2.getTexture(), final2);
}

void EndGame::renderSurvival() {
    SDL_Color color = COLOR_WHITE;
    int w, h, w2, h2;
    font.getSizeFont(TEXT_SURVIVAL, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_SURVIVAL, color));
    SDL_Rect final = { 650, 430, w, h};
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { 574, 375, SPRITE_BG_W, SPRITE_BG_H * 2};
    this->renderer.copy(textures.getTexture("healthbg"), rectInit,
                        rectFinal);
    this->renderer.copyFont(textureFont.getTexture(), final);
    // id // kills // time // shots
    font.getSizeFont(TEXT_STATS, &w2, &h2);
    Texture textureFont2(renderer, font.RenderText_Solid(TEXT_STATS, color));
    SDL_Rect final2 = { 600, final.y + h2 + 10, w2, h2};
    int height = final.y + h2;
    this->renderer.copyFont(textureFont2.getTexture(), final2);
    int n;
    for  (size_t i = 0; i < stats.size(); i++) {
        n = this->renderStats(height, stats[i]);
        height = n;
    }
}

int EndGame::renderStats(int height, StatsDto dto) {
     SDL_Color color = COLOR_WHITE;
    int w, h;
    std::string text =  std::to_string(dto.getPlayerId()) + "  " +
                        std::to_string(dto.getShots()) + "  " +
                        std::to_string(dto.getKills()) + "  " +
                        std::to_string(dto.getMinutes()) + ":" +
                        std::to_string(dto.getSeconds());
    font.getSizeFont(text, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(text, color));
    SDL_Rect final = {  620, height + h + 10, w, h};
    this->renderer.copyFont(textureFont.getTexture(), final);
    return h + final.y - 10;
}

void EndGame::addStats(std::vector<StatsDto> stats) {
    this->stats = std::move(stats);
}
