#ifndef LEFT4DEAD_SMOKEGRENADECOMMAND_H
#define LEFT4DEAD_SMOKEGRENADECOMMAND_H

#include "Command.h"


class SmokeGrenadeCommand  : public Command {
    private:
        uint8_t id;

    public:
        SmokeGrenadeCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~SmokeGrenadeCommand() override;
};


#endif //LEFT4DEAD_SMOKEGRENADECOMMAND_H
