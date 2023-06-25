#ifndef LEFT4DEAD_SHOOTCOMMAND_H
#define LEFT4DEAD_SHOOTCOMMAND_H

#include "Command.h"
#include "Move.h"

class ShootCommand : public Command {
    private:
        uint8_t id;

    public:
        explicit ShootCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~ShootCommand() override;
};

#endif //LEFT4DEAD_SHOOTCOMMAND_H
