#include "CheatInfinityLifeCommand.h"

CheatInfinityLifeCommand::CheatInfinityLifeCommand(uint8_t id) {}

void CheatInfinityLifeCommand::execute(GameWorld &gameWorld) {
    gameWorld.makeInmortal(Event::event_cheat_infinite_health, id);
}

CheatInfinityLifeCommand::~CheatInfinityLifeCommand() = default;
