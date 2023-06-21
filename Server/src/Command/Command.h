#ifndef LEFT4DEAD_COMMAND_H
#define LEFT4DEAD_COMMAND_H

#include "GameWorld.h"

class Command {
    public:
        Command();
        virtual void execute(GameWorld& gameWorld) = 0;

        virtual ~Command() = default;
};


#endif //LEFT4DEAD_COMMAND_H
