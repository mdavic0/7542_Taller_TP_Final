#ifndef MAPSDL_H_
#define MAPDSL_H_

#include "RendererSdl.h"
#include "TextureSdl.h"
#include "WindowSdl.h"
#include <map>
#include <string>
#include <memory>

class MapSdl {
    private:
        uint8_t mapId;
        Renderer& renderMap;
        WindowSdl& window;
        std::map<std::string, std::shared_ptr<Texture>> textures;
        void chargeTexture(Renderer& renderer);
        int repetitions;
    public:
        MapSdl(uint8_t id, Renderer& renderer, WindowSdl& window);
        ~MapSdl();
        void render(SDL_Rect camera);
};

#endif
