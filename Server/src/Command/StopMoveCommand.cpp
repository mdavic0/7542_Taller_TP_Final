#include "StopMoveCommand.h"

StopMoveCommand::StopMoveCommand(uint8_t id, MoveTo moveTo) : id(id), moveTo(moveTo) {}

void StopMoveCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateMovementDirection(Event::event_stop_move, this->id, this->moveTo);
}

StopMoveCommand::~StopMoveCommand() = default;


