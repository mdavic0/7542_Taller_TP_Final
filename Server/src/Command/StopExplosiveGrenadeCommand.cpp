#include "StopExplosiveGrenadeCommand.h"

StopExplosiveGrenadeCommand::StopExplosiveGrenadeCommand(uint8_t id) : id(id) {}

void StopExplosiveGrenadeCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateSkillState(Event::event_stop_grenade, this->id);
}

StopExplosiveGrenadeCommand::~StopExplosiveGrenadeCommand() = default;
