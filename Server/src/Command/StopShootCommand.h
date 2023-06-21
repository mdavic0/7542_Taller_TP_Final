#ifndef LEFT4DEAD_STOPSHOOTCOMMAND_H
#define LEFT4DEAD_STOPSHOOTCOMMAND_H


#include "Command.h"
#include "Move.h"

class StopShootCommand : public Command {
    private:
        uint8_t id;

    public:
        StopShootCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~StopShootCommand() override;
};


#endif //LEFT4DEAD_STOPSHOOTCOMMAND_H
