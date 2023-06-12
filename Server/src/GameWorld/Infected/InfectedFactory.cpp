#include "InfectedFactory.h"

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateInfecteds(TypeDifficulty typeDifficulty, uint8_t &infectedId,
                                   std::map<uint8_t, std::shared_ptr<Collidable>>& collidables) {
    switch (typeDifficulty) {
        case TypeDifficulty::difficulty_easy:
            return generateEasyInfecteds(infectedId, collidables);
            break;
        case TypeDifficulty::difficulty_normal:
            return generateNormalInfecteds(infectedId, collidables);
            break;
        case TypeDifficulty::difficulty_hard:
            return generateHardInfecteds(infectedId, collidables);
            break;
        case TypeDifficulty::difficulty_god:
            return generateGodInfecteds(infectedId, collidables);
            break;
        default:
            return generateNormalInfecteds(infectedId, collidables);
            break;
    }
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateEasyInfecteds(uint8_t &infectedId,
                                       std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateNormalInfecteds(uint8_t &infectedId,
                                         std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateHardInfecteds(uint8_t &infectedId,
                                       std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables)});
    infectedId++;

    return infecteds;
}

std::map<uint8_t, std::shared_ptr<Infected>>
InfectedFactory::generateGodInfecteds(uint8_t &infectedId,
                                      std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    std::map<uint8_t, std::shared_ptr<Infected>> infecteds;

    infecteds.insert({infectedId, createZombie(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createSpear(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createVenom(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createJumper(infectedId, collidables)});
    infectedId++;
    infecteds.insert({infectedId, createWitch(infectedId, collidables)});
    infectedId++;

    return infecteds;
}

// TODO: CREATE POSITION CONTROLLER whos controll the available respawn positions??
//      and can generate random respawn pos
std::shared_ptr<Infected>
InfectedFactory::createZombie(uint8_t &infectedId,
                              std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    // Zombie:
    std::shared_ptr<Infected> zombie = nullptr;

    std::pair<int16_t, int16_t> zombie_position = {(WINDOW_WIDTH / 2) - 50,
                                                   (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) - 25};

    std::shared_ptr<Collidable> zombie_collidable =  std::make_shared<Collidable>(
            infectedId, zombie_position, 20,  20);

    zombie = std::make_shared<Zombie>(infectedId, zombie_position, zombie_collidable);

    collidables.insert({infectedId, zombie_collidable});

    return zombie;
}

std::shared_ptr<Infected>
InfectedFactory::createSpear(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    // Spear:
    std::shared_ptr<Infected> spear = nullptr;

    std::pair<int16_t, int16_t> spear_position = {(WINDOW_WIDTH / 2) - 50,
                                                  (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5)};

    std::shared_ptr<Collidable> spear_collidable =  std::make_shared<Collidable>(
            infectedId, spear_position, 20,  20);

    spear = std::make_shared<Spear>(infectedId, spear_position, spear_collidable);

    collidables.insert({infectedId, spear_collidable});

    return spear;
}

std::shared_ptr<Infected>
InfectedFactory::createJumper(uint8_t &infectedId,
                              std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    // Jumper:
    std::shared_ptr<Infected> jumper = nullptr;

    std::pair<int16_t, int16_t> jumper_position = {(WINDOW_WIDTH / 2) - 50,
                                                   (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 50};

    std::shared_ptr<Collidable> jumper_collidable =  std::make_shared<Collidable>(
            infectedId, jumper_position,20, 20);

    jumper = std::make_shared<Jumper>(infectedId, jumper_position, jumper_collidable);

    collidables.insert({infectedId, jumper_collidable});

    return jumper;
}

std::shared_ptr<Infected>
InfectedFactory::createWitch(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    // Witch
    std::shared_ptr<Infected> witch = nullptr;

    std::pair<int16_t, int16_t> witch_position = {(WINDOW_WIDTH / 2) - 50,
                                                  (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 75};

    std::shared_ptr<Collidable> witch_collidable =  std::make_shared<Collidable>(
            infectedId,witch_position,20, 20);

    witch = std::make_shared<Witch>(infectedId, witch_position, witch_collidable);

    collidables.insert({infectedId, witch_collidable});

    return witch;
}

std::shared_ptr<Infected>
InfectedFactory::createVenom(uint8_t &infectedId,
                             std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    // Venom:
    std::shared_ptr<Infected> venom = nullptr;

    std::pair<int16_t, int16_t> venom_position = {(WINDOW_WIDTH / 2) - 50,
                                                  (WINDOW_HEIGTH / 2) + (WINDOW_HEIGTH / 3.5) + 25};

    std::shared_ptr<Collidable> venom_collidable =  std::make_shared<Collidable>(
            infectedId,venom_position,20, 20);

    venom = std::make_shared<Venom>(infectedId, venom_position, venom_collidable);

    collidables.insert({infectedId, venom_collidable});

    return venom;
}
