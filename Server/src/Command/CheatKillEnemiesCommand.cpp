#include "CheatKillEnemiesCommand.h"


CheatKillEnemiesCommand::CheatKillEnemiesCommand(uint8_t id) : id(id) {}

void CheatKillEnemiesCommand::execute(GameWorld &gameWorld) {
    gameWorld.killInfecteds(Event::event_cheat_kill_enemies, id);
}

CheatKillEnemiesCommand::~CheatKillEnemiesCommand() = default;
