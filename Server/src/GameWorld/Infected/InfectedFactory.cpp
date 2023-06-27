#include "InfectedFactory.h"

std::map<uint16_t, std::shared_ptr<Infected>>
InfectedFactory::generateInfecteds(TypeDifficulty typeDifficulty, uint16_t &infectedId,
                                   std::map<uint16_t, std::shared_ptr<Collidable>>& collidables,
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

std::map<uint16_t, std::shared_ptr<Infected>>
InfectedFactory::generateEasyInfecteds(uint16_t &infectedId,
                                       std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                       RespawnController& RC) {
    std::map<uint16_t, std::shared_ptr<Infected>> infecteds;

    // Zombies
    for (int i = 0; i < CF::zombie_amount_easy; i++) {
        infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
        infectedId++;
    }

    // Spears
    for (int i = 0; i < CF::spear_amount_easy; i++) {
        infecteds.insert({infectedId, createSpear(infectedId, collidables, RC)});
        infectedId++;
    }

    // Venoms
    for (int i = 0; i < CF::venom_amount_easy; i++) {
        infecteds.insert({infectedId, createVenom(infectedId, collidables, RC)});
        infectedId++;
    }

    // Jumpers
    for (int i = 0; i < CF::jumper_amount_easy; i++) {
        infecteds.insert({infectedId, createJumper(infectedId, collidables, RC)});
        infectedId++;
    }

    // Witches
    for (int i = 0; i < CF::witch_amount_easy; i++) {
        infecteds.insert({infectedId, createWitch(infectedId, collidables, RC)});
        infectedId++;
    }

    return infecteds;
}

std::map<uint16_t, std::shared_ptr<Infected>>
InfectedFactory::generateNormalInfecteds(uint16_t &infectedId,
                                         std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                         RespawnController& RC) {
    std::map<uint16_t, std::shared_ptr<Infected>> infecteds;

    // Zombies
    for (int i = 0; i < CF::zombie_amount_normal; i++) {
        infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
        infectedId++;
    }

    // Spears
    for (int i = 0; i < CF::spear_amount_normal; i++) {
        infecteds.insert({infectedId, createSpear(infectedId, collidables, RC)});
        infectedId++;
    }

    // Venoms
    for (int i = 0; i < CF::venom_amount_normal; i++) {
        infecteds.insert({infectedId, createVenom(infectedId, collidables, RC)});
        infectedId++;
    }

    // Jumpers
    for (int i = 0; i < CF::jumper_amount_normal; i++) {
        infecteds.insert({infectedId, createJumper(infectedId, collidables, RC)});
        infectedId++;
    }

    // Witches
    for (int i = 0; i < CF::witch_amount_normal; i++) {
        infecteds.insert({infectedId, createWitch(infectedId, collidables, RC)});
        infectedId++;
    }

    return infecteds;
}

std::map<uint16_t, std::shared_ptr<Infected>>
InfectedFactory::generateHardInfecteds(uint16_t &infectedId,
                                       std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                       RespawnController& RC) {
    std::map<uint16_t, std::shared_ptr<Infected>> infecteds;

    // Zombies
    for (int i = 0; i < CF::zombie_amount_hard; i++) {
        infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
        infectedId++;
    }

    // Spears
    for (int i = 0; i < CF::spear_amount_hard; i++) {
        infecteds.insert({infectedId, createSpear(infectedId, collidables, RC)});
        infectedId++;
    }

    // Venoms
    for (int i = 0; i < CF::venom_amount_hard; i++) {
        infecteds.insert({infectedId, createVenom(infectedId, collidables, RC)});
        infectedId++;
    }

    // Jumpers
    for (int i = 0; i < CF::jumper_amount_hard; i++) {
        infecteds.insert({infectedId, createJumper(infectedId, collidables, RC)});
        infectedId++;
    }

    // Witches
    for (int i = 0; i < CF::witch_amount_hard; i++) {
        infecteds.insert({infectedId, createWitch(infectedId, collidables, RC)});
        infectedId++;
    }

    return infecteds;
}

std::map<uint16_t, std::shared_ptr<Infected>>
InfectedFactory::generateGodInfecteds(uint16_t &infectedId,
                                      std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
                                      RespawnController& RC) {
    std::map<uint16_t, std::shared_ptr<Infected>> infecteds;

    // Zombies
    for (int i = 0; i < CF::zombie_amount_god; i++) {
        infecteds.insert({infectedId, createZombie(infectedId, collidables,RC)});
        infectedId++;
    }

    // Spears
    for (int i = 0; i < CF::spear_amount_god; i++) {
        infecteds.insert({infectedId, createSpear(infectedId, collidables, RC)});
        infectedId++;
    }

    // Venoms
    for (int i = 0; i < CF::venom_amount_god; i++) {
        infecteds.insert({infectedId, createVenom(infectedId, collidables, RC)});
        infectedId++;
    }

    // Jumpers
    for (int i = 0; i < CF::jumper_amount_god; i++) {
        infecteds.insert({infectedId, createJumper(infectedId, collidables, RC)});
        infectedId++;
    }

    // Witches
    for (int i = 0; i < CF::witch_amount_god; i++) {
        infecteds.insert({infectedId, createWitch(infectedId, collidables, RC)});
        infectedId++;
    }

    return infecteds;
}

std::shared_ptr<Infected>
InfectedFactory::createZombie(uint16_t &infectedId,
                              std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
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
InfectedFactory::createSpear(uint16_t &infectedId,
                             std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
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
InfectedFactory::createJumper(uint16_t &infectedId,
                              std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
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
InfectedFactory::createWitch(uint16_t &infectedId,
                             std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
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
InfectedFactory::createVenom(uint16_t &infectedId,
                             std::map<uint16_t, std::shared_ptr<Collidable>> &collidables,
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
