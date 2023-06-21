#ifndef LEFT4DEAD_MOVECOMMAND_H
#define LEFT4DEAD_MOVECOMMAND_H

#include "Command.h"
#include "Move.h"

class MoveCommand : public Command {
    private:
        uint8_t id;
        MoveTo moveTo;

    public:
        MoveCommand(uint8_t id, MoveTo moveTo);
        void execute(GameWorld& gameWorld) override;
        ~MoveCommand() override;
};


#endif //LEFT4DEAD_MOVECOMMAND_H
