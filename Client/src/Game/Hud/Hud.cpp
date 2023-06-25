#include "Hud.h"
#include "Configuration.h"
#include "Defines.h"
#include <iostream>

Hud::Hud(TypeOperator type, TypeGame game, Renderer& render, Font& font,
    WindowSdl& window) : type(type), gameType(game), renderHud(render),
    healthInit(0), munitionInit(0), enemiesDeath(0), fontHud(font),
    window(window) {
    this->loadTextures();
    switch (type) {
        case TypeOperator::operator_idf:
            healthInit = CF::idf_health;
            munitionInit = CF::idf_capacity;
            break;
        case TypeOperator::operator_p90:
            healthInit = CF::p90_health;
            munitionInit = CF::p90_capacity;
            break;
        case TypeOperator::operator_scout:
            healthInit = CF::scout_health;
            munitionInit = CF::scout_capacity;
            break;    
        default:
            break;
    }
}

void Hud::loadTextures() {
    std::string path = "assets/images/sdl/hud/";
    texturesHud["healthbg"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg.png");
    texturesHud["bar-bg"] = std::make_unique<Texture>(
                                    renderHud, path + "bar_bg.png");
    texturesHud["bar-fill"] = std::make_unique<Texture>(
                                    renderHud, path + "bar_fill.png");
    texturesHud["health-icon"] = std::make_unique<Texture>(
                                    renderHud, path + "health_icon.png");
    texturesHud["rifle"] = std::make_unique<Texture>(
                                    renderHud, path + "icon_rifle.png");
    texturesHud["hunting"] = std::make_unique<Texture>(
                                    renderHud, path + "icon_hunting.png");
    texturesHud["bullet-rifle"] = std::make_unique<Texture>(
                                    renderHud, path + "bullet_rifle.png");
    texturesHud["bullet-hunting"] = std::make_unique<Texture>(
                                    renderHud, path + "bullet_hunting.png");
    texturesHud["blitz"] = std::make_unique<Texture>(
                                    renderHud, path + "blitz.png");
    texturesHud["notblitz"] = std::make_unique<Texture>(
                                    renderHud, path + "notBlitz.png");
    texturesHud["grenade"] = std::make_unique<Texture>(
                                    renderHud, path + "grenade.png");
    texturesHud["notGrenade"] = std::make_unique<Texture>(
                                    renderHud, path + "notGrenade.png");
    texturesHud["smoke"] = std::make_unique<Texture>(
                                    renderHud, path + "smoke.png");
    texturesHud["notSmoke"] = std::make_unique<Texture>(
                                    renderHud, path + "notSmoke.png");
    
}

void Hud::render(uint8_t healthPlayer, int numBullet, size_t size,
    bool grenade, bool smoke) {
    this->renderBg();
    this->renderHealthBar();
    this->renderHealthIcon();
    this->renderHealthFill(healthPlayer);
    this->renderIconWeapon();
    this->renderIconBullet();
    this->renderNumBullet(numBullet);
    this->renderGrenades(grenade, smoke);
    this->renderBgMode();
    this->renderTextMode(size);
}

void Hud::renderBg() {
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = { 5, 30, SPRITE_BG_W * 19 / 10, SPRITE_BG_H};
    window.adjustedRect(rectFinal);
    this->renderHud.copy(texturesHud["healthbg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthBar() {
    SDL_Rect rectInit = { 0, 0, HEALTH_BG_W, SIZE_SPRITE_64};
    SDL_Rect rectFinal = { 68, 65, HEALTH_BG_W, SIZE_SPRITE_64};
    window.adjustedRect(rectFinal);
    this->renderHud.copy(texturesHud["bar-bg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthIcon() {
    SDL_Rect rectInit = { 0, 0, SIZE_SPRITE_64, SIZE_SPRITE_64};
    SDL_Rect rectFinal = { 32, 72, SIZE_SPRITE_64 * 7 / 10, SIZE_SPRITE_64 * 7 / 10};
    window.adjustedRect(rectFinal);
    this->renderHud.copy(texturesHud["health-icon"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthFill(uint8_t healthPlayer) {
    SDL_Rect rectInit = { 0, 0,
                    HEALTH_FILL_W * healthPlayer / healthInit, HEALTH_FILL_H};
    SDL_Rect rectFinal = { 82, 84,
                    HEALTH_FILL_W * healthPlayer / healthInit, HEALTH_FILL_H};
    window.adjustedRect(rectFinal);
    this->renderHud.copy(texturesHud["bar-fill"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderIconWeapon() {
    SDL_Rect rectInit = { 0, 0, 512, SIZE_FRAME};
    SDL_Rect rectFinal = { 68, 110, 512 * 1 / 4, SIZE_FRAME * 1 / 4};
    window.adjustedRect(rectFinal);
    if (type == TypeOperator::operator_scout)
        this->renderHud.copy(texturesHud["hunting"]->getTexture(), rectInit,
                            rectFinal, SDL_FLIP_HORIZONTAL);
    else if (type == TypeOperator::operator_idf || 
            type == TypeOperator::operator_p90)
        this->renderHud.copy(texturesHud["rifle"]->getTexture(), rectInit,
                            rectFinal, SDL_FLIP_HORIZONTAL);
}

void Hud::renderIconBullet() {
    SDL_Rect rectInit;
    SDL_Rect rectFinal = { 240, 110, SIZE_SPRITE_32, SIZE_SPRITE_32};
    window.adjustedRect(rectFinal);
    if (type == TypeOperator::operator_scout){
        rectInit = {0, 0, SIZE_SPRITE_64, SIZE_SPRITE_64};
        this->renderHud.copy(texturesHud["bullet-hunting"]->getTexture(),
                        rectInit, rectFinal);
    } else if (type == TypeOperator::operator_idf || 
            type == TypeOperator::operator_p90) {
        rectInit = {0, 0, SIZE_SPRITE_32, SIZE_SPRITE_32};
        this->renderHud.copy(texturesHud["bullet-rifle"]->getTexture(),
                            rectInit, rectFinal);
    }
}

void Hud::renderGrenades(bool grenade, bool smoke) {
    SDL_Rect rectInit = {0, 0, SIZE_SPRITE_64, SIZE_SPRITE_64};
    SDL_Rect rectFinal = { 280, 110, SIZE_SPRITE_32, SIZE_SPRITE_32};
    if (type == TypeOperator::operator_p90){
        window.adjustedRect(rectFinal);
        if (grenade) {
            this->renderHud.copy(texturesHud["blitz"]->getTexture(),
                        rectInit, rectFinal);
        } else {
            this->renderHud.copy(texturesHud["notBlitz"]->getTexture(),
                        rectInit, rectFinal);
        }
    } else if (type == TypeOperator::operator_idf || 
            type == TypeOperator::operator_scout) {
        window.adjustedRect(rectFinal);
        if (grenade) {
            this->renderHud.copy(texturesHud["grenade"]->getTexture(),
                        rectInit, rectFinal);
        } else {
            this->renderHud.copy(texturesHud["notGrenade"]->getTexture(),
                        rectInit, rectFinal);
        }
        rectFinal = { 320, 110, SIZE_SPRITE_32, SIZE_SPRITE_32};;
        window.adjustedRect(rectFinal);
        if (smoke) {
            this->renderHud.copy(texturesHud["smoke"]->getTexture(),
                        rectInit, rectFinal);
        } else {
            this->renderHud.copy(texturesHud["notSmoke"]->getTexture(),
                        rectInit, rectFinal);
        }
    }
}

void Hud::renderNumBullet(int numBullet) {
    SDL_Color color = COLOR_WHITE;
    int w, h;
    std::string text = std::to_string(numBullet) + "I" + 
                        std::to_string(munitionInit);
    this->fontHud.getSizeFont(text, &w, &h);
    Texture textureFont(renderHud, fontHud.RenderText_Solid(text, color));
    SDL_Rect final = { 180, 120, w, h};
    window.adjustedRect(final);
    this->renderHud.copyFont(textureFont.getTexture(), final);
}

void Hud::renderBgMode() {
    SDL_Rect rectInit = { 0, 0, SPRITE_BG_W, SPRITE_BG_H};
    SDL_Rect rectFinal = {1100, 30, SPRITE_BG_W * 11 / 10, SPRITE_BG_H};
    window.adjustedRect(rectFinal);
    this->renderHud.copy(texturesHud["healthbg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderTextMode(size_t size) {
    SDL_Color color = COLOR_WHITE;
    int w, h; // w2, h2;
    std::string text = " ";
    std::string text2 = std::to_string(size);
    if (gameType == TypeGame::game_clear_zone)
        text = "Remaining enemies: " + text2;
    else if (gameType == TypeGame::game_survival)
        text = "Enemies eliminated";
    this->fontHud.getSizeFont(text, &w, &h);
    Texture textureFont(renderHud, fontHud.RenderText_Solid(text, color));
    SDL_Rect rectFinal = {1120, 80 + h, w, h};
    window.adjustedRect(rectFinal);
    this->renderHud.copyFont(textureFont.getTexture(), rectFinal);
}

Hud::~Hud() {
}

