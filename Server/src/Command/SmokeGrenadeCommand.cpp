#include "SmokeGrenadeCommand.h"

SmokeGrenadeCommand::SmokeGrenadeCommand(uint8_t id) : id(id) {}

void SmokeGrenadeCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateSkillState(Event::event_throw_smoke, this->id);
}

SmokeGrenadeCommand::~SmokeGrenadeCommand() = default;
