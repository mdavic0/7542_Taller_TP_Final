#include <memory>
#include "CommandFactory.h"
#include "MoveCommand.h"
#include "StopMoveCommand.h"
#include "ShootCommand.h"
#include "StopShootCommand.h"
#include "LeaveCommand.h"

CommandFactory::CommandFactory() = default;

std::unique_ptr <Command> CommandFactory::getCommand(std::shared_ptr <EventDTO> event) {
    switch (event->getEvent()) {
        case Event::event_move:
            return std::make_unique<MoveCommand>(event->getIdPlayer(), event->getMoveTo());
        case Event::event_stop_move:
            return std::make_unique<StopMoveCommand>(event->getIdPlayer(), event->getMoveTo());
        case Event::event_shoot:
            return std::make_unique<ShootCommand>(event->getIdPlayer());
        case Event::event_stop_shoot:
            return std::make_unique<StopShootCommand>(event->getIdPlayer());
        /*case Event::event_throw_smoke:
            break;
        case Event::event_stop_smoke:
            break;
        case Event::event_throw_grenade:
            break;
        case Event::event_stop_grenade:
            break;
        case Event::event_blitz_atack:
            break;*/
        case Event::event_leave:
            return std::make_unique<LeaveCommand>(event->getIdPlayer());
        default:
            return nullptr;
    }
}
