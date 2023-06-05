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

GameDrawner::GameDrawner(Queue<std::shared_ptr<Snapshot>> &snapshot_queue,
    Queue<std::shared_ptr<EventDTO>> &client_events, bool& endGame, int menu) :
    client_events(client_events), snapshot_queue(snapshot_queue),
    endGame(endGame), menu(menu) {
}

void GameDrawner::run() {
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
            this->renderText(text1, text2, render, font);
        else if (menu == CREATE_MENU)
            this->renderText(text1, text3, render, font);
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    noReady = false;
                    game = false;
                    std::cout << "Cerre el juego\n";
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_RETURN) {
                        if (menu == CREATE_MENU) {
                            client_events.push(std::make_shared<EventDTO>(Event::event_start_game));
                            noReady = false;
                            std::cout << "presione enter\n";
                        }
                        // client_events.push(
                        //     new EventDTO(Event::event_start_game));
                    }
                    break;
                default:
                    break;
            }
        }
        render.present();
        SDL_Delay(1000 / 40);
    }    
    // map<<typeOperator, state>, <x,y>> players = ;
    // map<<Enemys, state>, <position>>
    // int map;
    // int mode;

    // mandar configuarcion una sola vez
    if (game) {
        GameSdl gameSdl(window, render, snapshot_queue, client_events, endGame, 1);
        
        // client_events.push(std::make_shared<EventDTO>(Event::event_start_game));
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
}

void GameDrawner::renderText(const std::string& text1, const std::string& text2,
    Renderer& render, Font& font) {
    SDL_Color color = {255, 255, 255, 255};
    int w, h, w2, h2; 
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
    render.copyFont(textureFont.getTexture(), final);
    render.copyFont(textureFont2.getTexture(), final2);
}

void GameDrawner::stop() {
}
