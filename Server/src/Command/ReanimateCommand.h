#ifndef LEFT4DEAD_REANIMATECOMMAND_H
#define LEFT4DEAD_REANIMATECOMMAND_H

#include "Command.h"


class ReanimateCommand : public Command {
    private:
        uint8_t id;

    public:
        explicit ReanimateCommand(uint8_t id);
        void execute(GameWorld &gameWorld) override;
        ~ReanimateCommand() override;
};


#endif //LEFT4DEAD_REANIMATECOMMAND_H
