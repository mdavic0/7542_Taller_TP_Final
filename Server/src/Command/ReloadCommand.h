#ifndef LEFT4DEAD_RELOADCOMMAND_H
#define LEFT4DEAD_RELOADCOMMAND_H

#include "Command.h"

class ReloadCommand  : public Command {
    private:
        uint8_t id;

    public:
        explicit ReloadCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~ReloadCommand() override;
};


#endif //LEFT4DEAD_RELOADCOMMAND_H
