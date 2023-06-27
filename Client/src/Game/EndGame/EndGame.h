#ifndef ENDGAME_H_
#define ENDGAME_H_

#include "Font.h"
#include "RendererSdl.h"
#include "TextureManager.h"
#include "TypeGame.h"
#include "StatsDto.h"
#include <vector>

class EndGame {
    private:
        Font& font;
        Renderer& renderer;
        TextureManager& textures;
        TypeGame type;
        WindowSdl& window;
        void renderClearZone();
        void renderSurvival();
        int renderStats(int height, StatsDto dto);
        int renderStatsName(int height);
        int renderRankings(int height, StatsDto dto);
        int renderRankingsName(int height);
        std::vector<StatsDto> stats;
    public:
        EndGame(Font& font, Renderer& renderer, TextureManager& textures,
                TypeGame type, WindowSdl& window);
        ~EndGame();
        void render();
        void addStats(std::vector<StatsDto> stats);
};

#endif
