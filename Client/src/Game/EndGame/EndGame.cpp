#include "EndGame.h"
#include "Defines.h"
#include <SDL2/SDL.h>
#include <algorithm>

EndGame::EndGame(Font& font, Renderer& renderer, TextureManager& textures,
    TypeGame type, WindowSdl& window, uint16_t idPlayer) : font(font),
    renderer(renderer), textures(textures), type(type), window(window),
    stats(), idPlayer(idPlayer) {
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
    int w, h, w2, h2, hf;
    font.getSizeFont(TEXT_SURVIVAL, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_SURVIVAL, color));
    SDL_Rect final = { 650, 430, w, h};
    hf = final.y;
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { 574, 300, SPRITE_BG_W, SPRITE_BG_H * 3};
    window.adjustedRect(final);
    window.adjustedRect(rectFinal);
    this->renderer.copy(textures.getTexture("healthbg"), rectInit,
                        rectFinal);
    this->renderer.copyFont(textureFont.getTexture(), final);
    hf = this->renderStatsName(hf);
    hf = this->renderRankingsName(hf);
    font.getSizeFont(TEXT_END_GAME, &w2, &h2);
    Texture textureFont2(renderer, font.RenderText_Solid(TEXT_END_GAME,
                                                        color));
    SDL_Rect final2 = { 600, hf + h2 + 10, w2, h2};
    window.adjustedRect(final2);
    this->renderer.copyFont(textureFont2.getTexture(), final2);
}

int EndGame::renderRankingsName(int height) {
    // Ranking
    SDL_Color color = COLOR_WHITE;
    int h, w, h2, w2, hf, hf2;
    font.getSizeFont(TEXT_RANKINGS, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_RANKINGS, color));
    SDL_Rect final = { 600, height + h + 10, w, h};
    hf = final.y - 10;
    // id // shots // kills // time 
    font.getSizeFont(TEXT_STATS, &w2, &h2);
    Texture textureFont2(renderer, font.RenderText_Solid(TEXT_STATS, color));
    SDL_Rect final2 = { 600, hf + h2 + 10, w2, h2};
    hf2 = final2.y - 10;
    window.adjustedRect(final);
    window.adjustedRect(final2);
    this->renderer.copyFont(textureFont.getTexture(), final);
    this->renderer.copyFont(textureFont2.getTexture(), final2);
    int id = idPlayer;
    auto it = std::find_if(stats.begin(), stats.end(),
        [id](const StatsDto& dto) {
            return dto.getPlayerId() == id;
    });
    int n = this->renderRankings(hf2, *it);
    return n;
}

int EndGame::renderRankings(int height, StatsDto dto) {
    SDL_Color color = COLOR_WHITE;
    int w, h, ret;
    std::string text =  std::to_string(dto.getRankingShots()) + "  " +
                        std::to_string(dto.getRankingKills()) + "  " +
                        std::to_string(dto.getRankingDuration());
    font.getSizeFont(text, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(text, color));
    SDL_Rect final = {  620, height + h + 10, w, h};
    ret = final.y - 10;
    window.adjustedRect(final);
    this->renderer.copyFont(textureFont.getTexture(), final);
    return ret;
}

int EndGame::renderStats(int height, StatsDto dto) {
    SDL_Color color = COLOR_WHITE;
    int w, h, ret;
    std::string text =  std::to_string(dto.getShots()) + "  " +
                        std::to_string(dto.getKills()) + "  " +
                        std::to_string(dto.getMinutes()) + ":" +
                        std::to_string(dto.getSeconds());
    font.getSizeFont(text, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(text, color));
    SDL_Rect final = {  620, height + h + 10, w, h};
    ret = final.y - 10;
    window.adjustedRect(final);
    this->renderer.copyFont(textureFont.getTexture(), final);
    return ret;
}

int EndGame::renderStatsName(int height) {
    // Stats
    // id // shots // kills // time 
    SDL_Color color = COLOR_WHITE;
    int h, w;
    font.getSizeFont(TEXT_STATS, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(TEXT_STATS, color));
    SDL_Rect final = { 600, height + h + 10, w, h};
    int hf = final.y - 10;
    window.adjustedRect(final);
    this->renderer.copyFont(textureFont.getTexture(), final);
    int id = idPlayer;
    auto it = std::find_if(stats.begin(), stats.end(),
        [id](const StatsDto& dto) {
            return dto.getPlayerId() == id;
    });
    int n = this->renderStats(hf, *it);
    return n;
}

void EndGame::addStats(std::vector<StatsDto> stats) {
    this->stats = std::move(stats);
}
