#ifndef LEFT4DEAD_CHEATSUPERSPEED_H
#define LEFT4DEAD_CHEATSUPERSPEED_H

#include "Command.h"


class CheatSuperSpeedCommand : public Command {
    private:
        uint8_t id;

    public:
        explicit CheatSuperSpeedCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~CheatSuperSpeedCommand() override;
};


#endif //LEFT4DEAD_CHEATSUPERSPEED_H
