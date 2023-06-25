#include "ReloadCommand.h"

ReloadCommand::ReloadCommand(uint8_t id) : id(id) {}

void ReloadCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateReloadingState(Event::event_recharge, this->id);
}

ReloadCommand::~ReloadCommand() = default;
