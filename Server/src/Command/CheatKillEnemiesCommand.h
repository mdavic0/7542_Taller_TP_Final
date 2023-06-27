#ifndef LEFT4DEAD_CHEATKILLENEMIESCOMMAND_H
#define LEFT4DEAD_CHEATKILLENEMIESCOMMAND_H

#include "Command.h"


class CheatKillEnemiesCommand : public Command {
    private:
        uint8_t id;

    public:
    explicit CheatKillEnemiesCommand(uint8_t id);
    void execute(GameWorld &gameWorld) override;
    ~CheatKillEnemiesCommand() override;
};


#endif //LEFT4DEAD_CHEATKILLENEMIESCOMMAND_H
