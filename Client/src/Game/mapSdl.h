#ifndef MAPSDL_H_
#define MAPDSL_H_

#include "RendererSdl.h"
#include "TextureSdl.h"
#include <map>
#include <string>

class MapSdl {
    private:
        uint8_t mapId;
        Renderer& renderMap;
        std::map<std::string, Texture*> textures;
        void chargeTexture(Renderer& renderer);
    public:
        MapSdl(uint8_t id, Renderer& renderer);
        ~MapSdl();
        void render();
};

#endif
