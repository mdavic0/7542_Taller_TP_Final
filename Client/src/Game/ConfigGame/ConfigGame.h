#ifndef CONFIG_GAME_H_
#define CONFIG_GAME_H_

#include <memory>
#include <map>
#include "Snapshot.h"
#include "Operator.h"
#include "Enemy.h"
#include "Obstacles.h"
#include "RendererSdl.h"
#include "TypeGame.h"
#include "TextureManager.h"
#include "ManagerMusic.h"
#include "WindowSdl.h"

class ConfigGame {
    private:  
        std::map<uint8_t, std::shared_ptr<Operator>> players;    
        std::map<uint8_t, std::shared_ptr<Enemy>> enemies;    
        std::map<uint8_t, std::shared_ptr<Obstacles>> obstacles;
        uint8_t idMap;
        TypeGame mode;
        TextureManager textures;
        ManagerMusic& music;
    public:
        ConfigGame(std::shared_ptr<Snapshot> config, Renderer& render,
                    WindowSdl& window, ManagerMusic& music);
        ~ConfigGame();
        std::map<uint8_t, std::shared_ptr<Operator>>& getPlayers();    
        std::map<uint8_t, std::shared_ptr<Enemy>>& getEnemies();    
        std::map<uint8_t, std::shared_ptr<Obstacles>>& getObstacles();
        TextureManager& getTextureManager();
        TypeGame getMode();
};

#endif
