#include "Hud.h"
#include "Configuration.h"
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
    SDL_Color c = {0, 0, 0, 255};
    texturesHud["healthbg"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg.png",c);
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
}

void Hud::render(uint8_t healthPlayer, int numBullet, size_t size) {
    this->renderBg();
    this->renderHealthBar();
    this->renderHealthIcon();
    this->renderHealthFill(healthPlayer);
    this->renderIconWeapon();
    this->renderIconBullet();
    this->renderNumBullet(numBullet);
    this->renderBgMode();
    this->renderTextMode(size);
}

void Hud::renderBg() {
    SDL_Rect rectInit = { 0, 0, 309, 188};
    SDL_Rect rectFinal = { 5, 30, 309 * 19 / 10, 188};
    window.adjustedRect(rectFinal, 309, 188);
    this->renderHud.copy(texturesHud["healthbg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthBar() {
    SDL_Rect rectInit = { 0, 0, 448, 64};
    SDL_Rect rectFinal = { 68, 65, 448, 64};
    window.adjustedRect(rectFinal, 448, 64);
    this->renderHud.copy(texturesHud["bar-bg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthIcon() {
    SDL_Rect rectInit = { 0, 0, 64, 64};
    SDL_Rect rectFinal = { 32, 72, 64 * 7 / 10, 64 * 7 / 10};
    window.adjustedRect(rectFinal, 64, 64);
    this->renderHud.copy(texturesHud["health-icon"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthFill(uint8_t healthPlayer) {
    SDL_Rect rectInit = { 0, 0, 410 * healthPlayer / healthInit, 21};
    SDL_Rect rectFinal = { 82, 84, 412 * healthPlayer / healthInit, 25};
    window.adjustedRect(rectFinal, 448, 64);
    this->renderHud.copy(texturesHud["bar-fill"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderIconWeapon() {
    SDL_Rect rectInit = { 0, 0, 512, 128};
    SDL_Rect rectFinal = { 68, 110, 512 * 1 / 4, 128 * 1 / 4};
    window.adjustedRect(rectFinal, 512, 128);
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
    SDL_Rect rectFinal = { 240, 110, 32, 32};
    // window.adjustedRect(rectFinal, 32, 32);
    if (type == TypeOperator::operator_scout){
        rectInit = {0, 0, 64, 64};
        this->renderHud.copy(texturesHud["bullet-hunting"]->getTexture(),
                        rectInit, rectFinal);
    } else if (type == TypeOperator::operator_idf || 
            type == TypeOperator::operator_p90) {
        rectInit = {0, 0, 32, 32};
        this->renderHud.copy(texturesHud["bullet-rifle"]->getTexture(),
                            rectInit, rectFinal);
    }
}

void Hud::renderNumBullet(int numBullet) {
    SDL_Color color = {255, 255, 255, 255};
    int w, h;
    std::string text = std::to_string(numBullet) + "I" + 
                        std::to_string(munitionInit);
    this->fontHud.getSizeFont(text, &w, &h);
    Texture textureFont(renderHud, fontHud.RenderText_Solid(text, color));
    SDL_Rect final = { 180, 120, w, h};
    this->renderHud.copyFont(textureFont.getTexture(), final);
}

void Hud::renderBgMode() {
    SDL_Rect rectInit = { 0, 0, 309, 188};
    SDL_Rect rectFinal = {window.getWidth() - rectFinal.w, 30, 309 * 11 / 10, 188};
    window.adjustedRect(rectFinal, 309, 188);
    this->renderHud.copy(texturesHud["healthbg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderTextMode(size_t size) {
    SDL_Color color = { 255, 255, 255, 255};
    int w, h; // w2, h2;
    std::string text = " ";
    std::string text2 = std::to_string(size);
    if (gameType == TypeGame::game_clear_zone)
        text = "Enemigos restantes: " + text2;
    else if (gameType == TypeGame::game_survival)
        text = "Enemigos eliminados";
    this->fontHud.getSizeFont(text, &w, &h);
    Texture textureFont(renderHud, fontHud.RenderText_Solid(text, color));
    SDL_Rect rectFinal = {window.getWidth() - w - 55, 80 + h, w, h};
    this->renderHud.copyFont(textureFont.getTexture(), rectFinal);
}

Hud::~Hud() {
}

