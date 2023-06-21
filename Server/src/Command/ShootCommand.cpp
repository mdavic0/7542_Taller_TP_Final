#include "ShootCommand.h"

ShootCommand::ShootCommand(uint8_t id) : id(id) {}

void ShootCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateShootingState(Event::event_shoot, this->id);
}

ShootCommand::~ShootCommand() = default;
