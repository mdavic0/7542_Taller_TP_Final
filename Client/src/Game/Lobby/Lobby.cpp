#include "Lobby.h"
#include "Defines.h"
#include "TextureSdl.h"
#include <iostream>

Lobby::Lobby(WindowSdl& window, Renderer& renderer, Font& font,
    Queue<std::shared_ptr<Snapshot>> &snapshotQueue,
    Queue<std::shared_ptr<EventDTO>> &eventQueue, int menu, bool& initGame,
    uint8_t idPlayer, uint8_t numPlayers) :
    window(window), renderer(renderer), font(font), snapshotQueue(snapshotQueue),
    eventQueue(eventQueue), menu(menu), initGame(initGame), idPlayer(idPlayer),
    numPlayers(numPlayers), snapConfig(nullptr) {
}

void Lobby::initLobby() {
    if (menu == JOIN_MENU)
        initLobbyJoin();
    else if (menu == CREATE_MENU)
        initLobbyCreate();
}

std::shared_ptr<Snapshot> Lobby::getConfigSnap() {
    return this->snapConfig;
}

void Lobby::initLobbyJoin() {
    std::string text1 = "Waiting for other players";
    std::string text2 = "Waiting for Ready";
    bool noReady = true;
        
    // Por si recibo el evento start_game
    std::shared_ptr<Snapshot> snap = nullptr;
    while(noReady)  {
        renderer.clear();
        render(text1, text2);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                        noReady = false;
                        initGame = false;
                        eventQueue.push(
                                std::make_shared<EventDTO>(Event::event_leave,
                                                            idPlayer));
                    }
                    break;
                default:
                    break;
            }
        }
        renderer.present();
        snapshotQueue.try_pop(snap);
        if (snap != nullptr && snap->getEvent() == Event::event_join)
            numPlayers = snap->getSize();
        else if (snap != nullptr && snap->getEvent() == Event::event_start_game)
            noReady = false;
        SDL_Delay(1000 / 40);
    }
    snapConfig = snap;
}

void Lobby::initLobbyCreate() {
    std::string text1 = "Waiting for other players";
    std::string text2 = "Press enter for play";
    bool noReady = true;

    std::shared_ptr<Snapshot> snap = nullptr;
    while(noReady)  {
        renderer.clear();
        render(text1, text2);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: {
                        noReady = false;
                        initGame = false;
                        eventQueue.push(
                                std::make_shared<EventDTO>(Event::event_leave,
                                                            idPlayer));
                    }
                    std::cout << "sali de sdl\n";
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        eventQueue.push(std::make_shared<EventDTO>(
                                    Event::event_start_game, 0));
                        noReady = false;
                    }
                    break;
                default:
                    break;
            }
        }
        renderer.present();
        snapshotQueue.try_pop(snap);
        if (snap != nullptr && snap->getEvent() == Event::event_join) {
            numPlayers = snap->getSize();
        } else if (snap != nullptr && 
                    snap->getEvent() == Event::event_start_game) {
            noReady = false;
            snapConfig = snap;
        }
        SDL_Delay(1000 / 40);
    }
    if (!snapConfig)
        snapshotQueue.try_pop(snapConfig);
}

void Lobby::render(const std::string& text1, const std::string& text2) {
    SDL_Color color = COLOR_WHITE;
    int w, h, w2, h2, w3, h3;
    font.getSizeFont(text1, &w, &h);
    Texture textureFont(renderer, font.RenderText_Solid(text1, color));
    SDL_Rect final = {  (window.getWidth() - w) / 2,
                        (window.getHeight() - h) / 2,
                        w,
                        h};
    font.getSizeFont(text2, &w2, &h2);
    Texture textureFont2(renderer,font.RenderText_Solid(text2, color));
    SDL_Rect final2 = { ((window.getWidth() - w2) / 2),
                        ((window.getHeight() - h) / 2) + h2 + 10,
                        w2,
                        h2};
    font.getSizeFont(text2, &w3, &h3);
    std::string text3 = "Connected Players: " + std::to_string(numPlayers);
    Texture textureFontPlayer(renderer, font.RenderText_Solid(text3, color));
    SDL_Rect final3 = {(window.getWidth() - w3 - 30), 15, w3, h3};
    renderer.copyFont(textureFontPlayer.getTexture(), final3);
    renderer.copyFont(textureFont.getTexture(), final);
    renderer.copyFont(textureFont2.getTexture(), final2);
}

Lobby::~Lobby() {
}

