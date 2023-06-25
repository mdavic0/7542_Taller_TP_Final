#ifndef LEFT4DEAD_STOPEXPLOSIVEGRENADECOMMAND_H
#define LEFT4DEAD_STOPEXPLOSIVEGRENADECOMMAND_H

#include "Command.h"


class StopExplosiveGrenadeCommand  : public Command {
    private:
        uint8_t id;

    public:
        StopExplosiveGrenadeCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~StopExplosiveGrenadeCommand() override;
};


#endif //LEFT4DEAD_STOPEXPLOSIVEGRENADECOMMAND_H
