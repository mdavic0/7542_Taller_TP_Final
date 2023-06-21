#include "StopShootCommand.h"

StopShootCommand::StopShootCommand(uint8_t id) : id(id) {}

void StopShootCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateShootingState(Event::event_stop_shoot, this->id);
}

StopShootCommand::~StopShootCommand() = default;
