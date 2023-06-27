#ifndef LEFT4DEAD_CHEATINFINITYLIFECOMMAND_H
#define LEFT4DEAD_CHEATINFINITYLIFECOMMAND_H

#include "Command.h"


class CheatInfinityLifeCommand : public Command {
    private:
        uint8_t id;

    public:
        explicit CheatInfinityLifeCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~CheatInfinityLifeCommand() override;
};


#endif //LEFT4DEAD_CHEATINFINITYLIFECOMMAND_H
