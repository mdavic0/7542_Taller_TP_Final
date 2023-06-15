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
    texturesHud["healthbg1"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg_1.png",c);
    texturesHud["healthbg2"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg_2.png", c);
    texturesHud["healthbg3"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg_3.png", c);
    texturesHud["healthbg4"] = std::make_unique<Texture>(
                                    renderHud, path + "healthbg_4.png", c);
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
    SDL_Rect rectInit = { 0, 0, 512, 256};
    SDL_Rect rectFinal = { 0, 0, 512 * 9 / 5, 256};
    // window.adjustedRect(rectInit, 512, 256);
    // window.adjustedRect(rectFinal, 512, 256);
    this->renderHud.copy(texturesHud["healthbg1"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg2"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg3"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg4"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthBar() {
    SDL_Rect rectInit = { 0, 0, 448, 64};
    SDL_Rect rectFinal = { 68, 65, 448, 64};
    this->renderHud.copy(texturesHud["bar-bg"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthIcon() {
    SDL_Rect rectInit = { 0, 0, 64, 64};
    SDL_Rect rectFinal = { 32, 72, 64 * 7 / 10, 64 * 7 / 10};
    this->renderHud.copy(texturesHud["health-icon"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderHealthFill(uint8_t healthPlayer) {
    SDL_Rect rectInit = { 0, 0, 448, 64};
    SDL_Rect rectFinal = { 68, 65, 448 * healthPlayer / healthInit, 64};
    this->renderHud.copy(texturesHud["bar-fill"]->getTexture(), rectInit,
                        rectFinal);
}

void Hud::renderIconWeapon() {
    SDL_Rect rectInit = { 0, 0, 512, 128};
    SDL_Rect rectFinal = { 68, 110, 512 * 1 / 4, 128 * 1 / 4};
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
    SDL_Rect rectInit = { 0, 0, 512, 256};
    SDL_Rect rectFinal = { 700, 0, 512, 256};
    this->renderHud.copy(texturesHud["healthbg1"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg2"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg3"]->getTexture(), rectInit,
                        rectFinal);
    this->renderHud.copy(texturesHud["healthbg4"]->getTexture(), rectInit,
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
    SDL_Rect rectFinal = { 720, 80, w, h};
    this->renderHud.copyFont(textureFont.getTexture(), rectFinal);
}

Hud::~Hud() {
}

