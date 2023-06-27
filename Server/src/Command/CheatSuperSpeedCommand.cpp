#include "CheatSuperSpeedCommand.h"


CheatSuperSpeedCommand::CheatSuperSpeedCommand(uint8_t id) : id(id) {}

void CheatSuperSpeedCommand::execute(GameWorld &gameWorld) {
    gameWorld.applySuperSpeed(Event::event_cheat_more_velocity, id);
}

CheatSuperSpeedCommand::~CheatSuperSpeedCommand() = default;
