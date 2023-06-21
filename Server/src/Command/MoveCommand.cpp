#include "MoveCommand.h"

MoveCommand::MoveCommand(uint8_t id, MoveTo moveTo) : id(id), moveTo(moveTo){}


void MoveCommand::execute(GameWorld &gameWorld) {
    gameWorld.updateMovementDirection(Event::event_move, this->id, this->moveTo);
}

MoveCommand::~MoveCommand() = default;
