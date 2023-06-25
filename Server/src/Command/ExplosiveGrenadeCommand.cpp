#include "ExplosiveGrenadeCommand.h"

ExplosiveGrenadeCommand::ExplosiveGrenadeCommand(uint8_t id) : id(id) {}

void ExplosiveGrenadeCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateSkillState(Event::event_throw_grenade, this->id);
}

ExplosiveGrenadeCommand::~ExplosiveGrenadeCommand() = default;
