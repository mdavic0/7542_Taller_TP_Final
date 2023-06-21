#ifndef LEFT4DEAD_STOPMOVECOMMAND_H
#define LEFT4DEAD_STOPMOVECOMMAND_H

#include "Command.h"
#include "Move.h"

class StopMoveCommand: public Command {
    private:
        uint8_t id;
        MoveTo moveTo;

    public:
        StopMoveCommand(uint8_t id, MoveTo moveTo);
        void execute(GameWorld& gameWorld) override;
        ~StopMoveCommand() override;
};


#endif //LEFT4DEAD_STOPMOVECOMMAND_H
