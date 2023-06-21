#include "LeaveCommand.h"

LeaveCommand::LeaveCommand(uint8_t id) : id(id) {}


void LeaveCommand::execute(GameWorld &gameWorld) {
    gameWorld.deletePlayer(this->id);
}

LeaveCommand::~LeaveCommand() = default;