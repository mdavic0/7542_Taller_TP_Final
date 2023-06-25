#ifndef LEFT4DEAD_STOPSMOKEGRENADECOMMAND_H
#define LEFT4DEAD_STOPSMOKEGRENADECOMMAND_H

#include "Command.h"


class StopSmokeGrenadeCommand  : public Command {
    private:
        uint8_t id;

    public:
        StopSmokeGrenadeCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~StopSmokeGrenadeCommand() override;
};


#endif //LEFT4DEAD_STOPSMOKEGRENADECOMMAND_H
