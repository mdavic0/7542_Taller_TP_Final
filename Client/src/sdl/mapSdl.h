#ifndef MAPSDL_H_
#define MAPDSL_H_

#include "client_rendererSdl.h"
#include "client_textureSdl.h"
#include <map>
#include <string>

class MapSdl {
    private:
        int mapId;
        Renderer& renderMap;
        std::map<std::string, Texture*> textures;
        void chargeTexture(Renderer& renderer);
    public:
        MapSdl(int id, Renderer& renderer);
        ~MapSdl();
        void render();
};

#endif
