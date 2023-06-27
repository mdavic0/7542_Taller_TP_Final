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
        std::map<uint16_t, std::shared_ptr<Infected>>
        generateInfecteds(TypeDifficulty typeDifficulty, uint16_t& infectedId,
                          std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                          RespawnController& RC);

    private:
        std::map<uint16_t, std::shared_ptr<Infected>>
        generateEasyInfecteds(uint16_t& infectedId,
                              std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                              RespawnController& RC);

        std::map<uint16_t, std::shared_ptr<Infected>>
        generateNormalInfecteds(uint16_t& infectedId, std::map<uint16_t,
                                std::shared_ptr<Collidable>>& collidables,
                                RespawnController& RC);

        std::map<uint16_t, std::shared_ptr<Infected>>
        generateHardInfecteds(uint16_t& infectedId,std::map<uint16_t,
                              std::shared_ptr<Collidable>>& collidables,
                              RespawnController& RC);

        std::map<uint16_t, std::shared_ptr<Infected>>
        generateGodInfecteds(uint16_t& infectedId,std::map<uint16_t,
                             std::shared_ptr<Collidable>>& collidables,
                             RespawnController& RC);

        std::shared_ptr<Infected>
        createZombie(uint16_t& infectedId,
                     std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);

        std::shared_ptr<Infected>
        createSpear(uint16_t& infectedId,
                    std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);

        std::shared_ptr<Infected>
        createJumper(uint16_t& infectedId,
                     std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                     RespawnController& RC);

        std::shared_ptr<Infected>
        createWitch(uint16_t& infectedId,
                    std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);

        std::shared_ptr<Infected>
        createVenom(uint16_t& infectedId,
                    std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
                    RespawnController& RC);
};


#endif //LEFT4DEAD_INFECTEDFACTORY_H
