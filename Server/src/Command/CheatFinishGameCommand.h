#ifndef LEFT4DEAD_CHEATFINISHGAMECOMMAND_H
#define LEFT4DEAD_CHEATFINISHGAMECOMMAND_H

#include "Command.h"


class CheatFinishGameCommand: public Command {
    private:
        uint8_t id;

    public:
        explicit CheatFinishGameCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~CheatFinishGameCommand() override;
};


#endif //LEFT4DEAD_CHEATFINISHGAMECOMMAND_H
