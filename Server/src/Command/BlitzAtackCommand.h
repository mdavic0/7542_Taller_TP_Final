#ifndef LEFT4DEAD_BLITZATACKCOMMAND_H
#define LEFT4DEAD_BLITZATACKCOMMAND_H

#include "Command.h"


class BlitzAtackCommand : public Command {
    private:
        uint8_t id;

    public:
        explicit BlitzAtackCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~BlitzAtackCommand() override;
};


#endif //LEFT4DEAD_BLITZATACKCOMMAND_H
