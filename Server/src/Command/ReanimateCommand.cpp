#include "ReanimateCommand.h"


ReanimateCommand::ReanimateCommand(uint8_t id) : id(id) {}

void ReanimateCommand::execute(GameWorld &gameWorld) {
    gameWorld.reanimatePlayer(Event::event_reanimate, this->id);
}

ReanimateCommand::~ReanimateCommand() = default;
