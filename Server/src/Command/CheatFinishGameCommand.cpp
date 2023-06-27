#include "CheatFinishGameCommand.h"


CheatFinishGameCommand::CheatFinishGameCommand(uint8_t id) : id(id) {}

void CheatFinishGameCommand::execute(GameWorld &gameWorld) {
    gameWorld.finishGame(Event::event_cheat_finish_game, id);
}

CheatFinishGameCommand::~CheatFinishGameCommand() = default;
