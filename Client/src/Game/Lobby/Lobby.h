#ifndef LOBBY_H_
#define LOBBY_H_

#include <memory>
#include "WindowSdl.h"
#include "RendererSdl.h"
#include "Font.h"
#include "Snapshot.h"
#include "EventDTO.h"
#include "Queue.h"

class Lobby  {
    private:
        WindowSdl& window;
        Renderer& renderer;
        Font& font;
        Queue<std::shared_ptr<Snapshot>> &snapshotQueue;
        Queue<std::shared_ptr<EventDTO>> &eventQueue;
        int menu;
        bool& initGame;
        uint8_t idPlayer;
        uint8_t numPlayers;
        std::shared_ptr<Snapshot> snapConfig;
        void initLobbyJoin();
        void initLobbyCreate();
        void render(const std::string& text1, const std::string& text2);
    public:
        Lobby(WindowSdl& window, Renderer& Renderer, Font& font,
                Queue<std::shared_ptr<Snapshot>> &snapshotQueue,
                Queue<std::shared_ptr<EventDTO>> &eventQueue, int menu,
                bool& initGame, uint8_t idPlayer, uint8_t numPlayers);
        ~Lobby();
        void initLobby();
        std::shared_ptr<Snapshot> getConfigSnap();
};

#endif
