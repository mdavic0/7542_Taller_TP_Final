#include "GameDrawner.h"
#include "GameSdl.h"
#include "RendererSdl.h"
#include "WindowSdl.h"
#include "Defines.h"
#include "Sdl.h"
#include "SdlImage.h"
#include "SdlTTF.h"
#include "SdlException.h"
#include "Font.h"
#include <map>
#include "Operator.h"

GameDrawner::GameDrawner(Queue<std::shared_ptr<Snapshot>> &snapshot_queue,
    Queue<std::shared_ptr<EventDTO>> &client_events, bool& endGame, int menu,
    uint8_t idPlayer) :
    client_events(client_events), snapshot_queue(snapshot_queue),
    endGame(endGame), menu(menu), cantPlayers(idPlayer + 1), idPlayer(idPlayer) {
}

void GameDrawner::run() {
    try {
        Sdl sdlInit(SDL_INIT_EVERYTHING);

        SdlImage sdlImage(IMG_INIT_PNG);

        SdlTTF sdlttf;

        WindowSdl window(   "Left 4 Dead",
                            SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED,
                            WINDOW_HEIGTH,
                            WINDOW_WIDTH,
                            SDL_WINDOW_SHOWN);

        Renderer render(window.getWindow(), -1, SDL_RENDERER_ACCELERATED);

        Font font("assets/font/Futurot.ttf", 20);
        font.setHinting();
        std::string text1 = "Waiting for other players";
        std::string text2 = "Waiting for Ready";
        std::string text3 = "Press enter for play";
        bool noReady = true;
        bool game = true;
        while(noReady)  {
            render.clear();
            if (menu == JOIN_MENU)
                this->renderText(text1, text2, render, font, cantPlayers);
            else if (menu == CREATE_MENU)
                this->renderText(text1, text3, render, font, cantPlayers);
            SDL_Event event;
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                    case SDL_QUIT: {
                            noReady = false;
                            game = false;
                            std::cout << "Cerre el juego\n";
                        }
                        break;
                    case SDL_KEYDOWN:
                        if (event.key.keysym.sym == SDLK_RETURN) {
                            if (menu == CREATE_MENU) {
                                client_events.push(
                                    std::make_shared<EventDTO>(
                                        Event::event_start_game));
                                noReady = false;
                                std::cout << "presione enter\n";
                            }
                        }
                        break;
                    default:
                        break;
                }
            }
            render.present();
            std::shared_ptr<Snapshot> snap = nullptr;
            snapshot_queue.try_pop(snap);
            if (snap != nullptr && snap->getEvent() == Event::event_join)
                cantPlayers++; // = snap->getAmountPlayers();
            else if (snap != nullptr && snap->getEvent() == Event::event_playing)
                noReady = false;
            SDL_Delay(1000 / 40);
        }
        // map<<typeOperator, state>, <x,y>> players = ;
        // map<<Enemys, state>, <position>>
        // int map;
        // int mode;

        if (game) {
            // mandar configuarcion una sola vez
            std::shared_ptr<Snapshot> snap = snapshot_queue.pop();
            std::map<uint8_t,Operator*> players;
            // int mode, map;

            for (auto &player : snap->getInfo()) {
                StOperator st = player.second;
                players[st.getId()] = new Operator(st.getId(), 
                    st.getTypeOperator(), render);
            }

            GameSdl gameSdl(window, render, snapshot_queue, client_events,
                            endGame, players, idPlayer);

            while (gameSdl.isRunning()) {
                uint32_t frameInit = SDL_GetTicks();

                render.clear();
                SDL_PumpEvents();
                    gameSdl.update();
                    gameSdl.handleEvents();
                    gameSdl.render();
                render.present();

                uint32_t frameEnd = SDL_GetTicks();
                uint32_t processTime = frameEnd - frameInit;

                if (1000 / 40 > processTime)
                    SDL_Delay(1000 / 40 - processTime);
            }
        }
        this->endGame = true;
        client_events.close();
    } catch (const SdlException &exc) {
        std::cerr << "Launcher: " << exc.what() << std::endl;
    } 
}

void GameDrawner::renderText(const std::string& text1, const std::string& text2,
    Renderer& render, Font& font, int& cantPlayers) {
    SDL_Color color = {255, 255, 255, 255};
    int w, h, w2, h2, w3, h3;
    font.getSizeFont(text1, &w, &h);
    Texture textureFont(render, font.RenderText_Solid(text1, color));
    SDL_Rect final = {  (WINDOW_WIDTH - w) / 2,
                        (WINDOW_HEIGTH - h) / 2,
                        w,
                        h};
    font.getSizeFont(text2, &w2, &h2);
    Texture textureFont2(render,font.RenderText_Solid(text2, color));
    SDL_Rect final2 = { ((WINDOW_WIDTH - w2) / 2),
                        ((WINDOW_HEIGTH - h) / 2) + h2 + 10,
                        w2,
                        h2};
    font.getSizeFont(text2, &w3, &h3);
    std::string text3 = "Connected Players: " + std::to_string(cantPlayers);
    Texture textureFontPlayer(render, font.RenderText_Solid(text3, color));
    SDL_Rect final3 = {(WINDOW_WIDTH - w3 - 30), 15, w3, h3};
    render.copyFont(textureFontPlayer.getTexture(), final3);
    render.copyFont(textureFont.getTexture(), final);
    render.copyFont(textureFont2.getTexture(), final2);
}

void GameDrawner::stop() {
}

GameDrawner::~GameDrawner() {
    join();
}