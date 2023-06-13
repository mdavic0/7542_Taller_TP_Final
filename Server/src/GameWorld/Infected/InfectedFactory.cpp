#include "InfectedFactory.h"

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateInfecteds(TypeDifficulty typeDifficulty, uint8_t &infectedId,
                                   std::map<uint8_t, std::shared_ptr<Collidable>>& collidables,
                                   RespawnController& RC) {
    switch (typeDifficulty) {
        case TypeDifficulty::difficulty_easy:
            return generateEasyInfecteds(infectedId, collidables, RC);
        case TypeDifficulty::difficulty_normal:
            return generateNormalInfecteds(infectedId, collidables, RC);
        case TypeDifficulty::difficulty_hard:
            return generateHardInfecteds(infectedId, collidables,RC);
        case TypeDifficulty::difficulty_god:
            return generateGodInfecteds(infectedId, collidables,RC);
        default:
            return generateNormalInfecteds(infectedId, collidables,RC);
    }
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateEasyInfecteds(uint8_t &infectedId,
                                       std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                                       RespawnController& RC) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables,RC)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateNormalInfecteds(uint8_t &infectedId,
                                         std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                                         RespawnController& RC) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables,RC)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateHardInfecteds(uint8_t &infectedId,
                                       std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                                       RespawnController& RC) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables,RC)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateGodInfecteds(uint8_t &infectedId,
                                      std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                                      RespawnController& RC) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables,RC)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables,RC)});
    infectedId++;

    return infecteds;
}

std::shared_ptr<Infected>
InfectedFactory::createZombie(uint8_t &infectedId,
                              std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                              RespawnController& RC) {
    // Zombie:
    std::shared_ptr<Infected> zombie = nullptr;

    std::pair<int16_t, int16_t> zombie_position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> zombie_collidable =  std::make_shared<Collidable>(
            infectedId, zombie_position, 20,  20);

    zombie = std::make_shared<Zombie>(infectedId, zombie_position, zombie_collidable);

    collidables.insert({infectedId, zombie_collidable});

    return zombie;
}

std::shared_ptr<Infected>
InfectedFactory::createSpear(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                             RespawnController& RC) {
    // Spear:
    std::shared_ptr<Infected> spear = nullptr;

    std::pair<int16_t, int16_t> spear_position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> spear_collidable =  std::make_shared<Collidable>(
            infectedId, spear_position, 20,  20);

    spear = std::make_shared<Spear>(infectedId, spear_position, spear_collidable);

    collidables.insert({infectedId, spear_collidable});

    return spear;
}

std::shared_ptr<Infected>
InfectedFactory::createJumper(uint8_t &infectedId,
                              std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                              RespawnController& RC) {
    // Jumper:
    std::shared_ptr<Infected> jumper = nullptr;

    std::pair<int16_t, int16_t> jumper_position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> jumper_collidable =  std::make_shared<Collidable>(
            infectedId, jumper_position,20, 20);

    jumper = std::make_shared<Jumper>(infectedId, jumper_position, jumper_collidable);

    collidables.insert({infectedId, jumper_collidable});

    return jumper;
}

std::shared_ptr<Infected>
InfectedFactory::createWitch(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                             RespawnController& RC) {
    // Witch
    std::shared_ptr<Infected> witch = nullptr;

    std::pair<int16_t, int16_t> witch_position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> witch_collidable =  std::make_shared<Collidable>(
            infectedId,witch_position,20, 20);

    witch = std::make_shared<Witch>(infectedId, witch_position, witch_collidable);

    collidables.insert({infectedId, witch_collidable});

    return witch;
}

std::shared_ptr<Infected>
InfectedFactory::createVenom(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables,
                             RespawnController& RC) {
    // Venom:
    std::shared_ptr<Infected> venom = nullptr;

    std::pair<int16_t, int16_t> venom_position = RC.getInfectedRespawnPosition();

    std::shared_ptr<Collidable> venom_collidable =  std::make_shared<Collidable>(
            infectedId,venom_position,20, 20);

    venom = std::make_shared<Venom>(infectedId, venom_position, venom_collidable);

    collidables.insert({infectedId, venom_collidable});

    return venom;
}
