#ifndef LEFT4DEAD_COMMANDFACTORY_H
#define LEFT4DEAD_COMMANDFACTORY_H

#include "Command.h"
#include "EventDTO.h"

class CommandFactory {

    public:
        CommandFactory();
        std::unique_ptr<Command> getCommand(std::shared_ptr<EventDTO> event);
};


#endif //LEFT4DEAD_COMMANDFACTORY_H
