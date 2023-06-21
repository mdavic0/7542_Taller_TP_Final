#ifndef LEFT4DEAD_INFECTEDFACTORY_H
#define LEFT4DEAD_INFECTEDFACTORY_H
#include "Infected.h"
#include "Collidable.h"
#include "Defines.h"
#include "Infected.h"
#include "Zombie.h"
#include "Spear.h"
#include "Witch.h"
#include "Jumper.h"
#include "Venom.h"
#include "TypeDifficulty.h"
#include "RespawnController.h"
#include "Configuration.h"


class InfectedFactory {
    public:
        std::map<uint8_t, std::shared_ptr<Infected>>
        generateInfecteds(TypeDifficulty typeDifficulty, uint8_t& infectedId,
                          std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                          RespawnController& RC);

    private:
        std::map<uint8_t, std::shared_ptr<Infected>>
        generateEasyInfecteds(uint8_t& infectedId,
                              std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                              RespawnController& RC);

        std::map<uint8_t, std::shared_ptr<Infected>>
        generateNormalInfecteds(uint8_t& infectedId, std::map<uint8_t,
                                std::shared_ptr<Collidable>>& collidables,
                                RespawnController& RC);

        std::map<uint8_t, std::shared_ptr<Infected>>
        generateHardInfecteds(uint8_t& infectedId,std::map<uint8_t,
                              std::shared_ptr<Collidable>>& collidables,
                              RespawnController& RC);

        std::map<uint8_t, std::shared_ptr<Infected>>
        generateGodInfecteds(uint8_t& infectedId,std::map<uint8_t,
                             std::shared_ptr<Collidable>>& collidables,
                             RespawnController& RC);

        std::shared_ptr<Infected>
        createZombie(uint8_t& infectedId,
                     std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);

        std::shared_ptr<Infected>
        createSpear(uint8_t& infectedId,
                    std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);

        std::shared_ptr<Infected>
        createJumper(uint8_t& infectedId,
                     std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);

        std::shared_ptr<Infected>
        createWitch(uint8_t& infectedId,
                    std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);

        std::shared_ptr<Infected>
        createVenom(uint8_t& infectedId,
                    std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);
};


#endif //LEFT4DEAD_INFECTEDFACTORY_H
