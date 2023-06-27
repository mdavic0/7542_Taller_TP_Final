#ifndef LEFT4DEAD_EXPLOSIVEGRENADECOMMAND_H
#define LEFT4DEAD_EXPLOSIVEGRENADECOMMAND_H

#include "Command.h"


class ExplosiveGrenadeCommand : public Command {
    private:
        uint8_t id;

    public:
        ExplosiveGrenadeCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~ExplosiveGrenadeCommand() override;
};


#endif //LEFT4DEAD_EXPLOSIVEGRENADECOMMAND_H
