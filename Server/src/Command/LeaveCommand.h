#ifndef LEFT4DEAD_LEAVECOMMAND_H
#define LEFT4DEAD_LEAVECOMMAND_H

#include "Command.h"
#include "Move.h"

class LeaveCommand : public Command {
    private:
        uint8_t id;

    public:
        LeaveCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~LeaveCommand() override;
};
#endif //LEFT4DEAD_LEAVECOMMAND_H
