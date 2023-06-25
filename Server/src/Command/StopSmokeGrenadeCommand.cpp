#include "StopSmokeGrenadeCommand.h"

StopSmokeGrenadeCommand::StopSmokeGrenadeCommand(uint8_t id) : id(id) {}

void StopSmokeGrenadeCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateSkillState(Event::event_stop_smoke, this->id);
}

StopSmokeGrenadeCommand::~StopSmokeGrenadeCommand() = default;
