#include "BlitzAtackCommand.h"

BlitzAtackCommand::BlitzAtackCommand(uint8_t id) : id(id) {}

void BlitzAtackCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateSkillState(Event::event_blitz_atack, this->id);
}

BlitzAtackCommand::~BlitzAtackCommand() = default;
