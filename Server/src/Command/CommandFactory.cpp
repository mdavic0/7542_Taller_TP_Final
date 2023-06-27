#include <memory>
#include "CommandFactory.h"
#include "MoveCommand.h"
#include "StopMoveCommand.h"
#include "ShootCommand.h"
#include "StopShootCommand.h"
#include "LeaveCommand.h"
#include "ReloadCommand.h"
#include "ExplosiveGrenadeCommand.h"
#include "StopExplosiveGrenadeCommand.h"
#include "SmokeGrenadeCommand.h"
#include "StopSmokeGrenadeCommand.h"
#include "BlitzAtackCommand.h"
#include "ReanimateCommand.h"
#include "CheatFinishGameCommand.h"
#include "CheatSuperSpeedCommand.h"
#include "CheatKillEnemiesCommand.h"


CommandFactory::CommandFactory() = default;

std::unique_ptr <Command> CommandFactory::getCommand(std::shared_ptr <EventDTO> event) {
    switch (event->getEvent()) {
        case Event::event_move:
            return std::make_unique<MoveCommand>(event->getIdPlayer(),
                                                 event->getMoveTo());
        case Event::event_stop_move:
            return std::make_unique<StopMoveCommand>(event->getIdPlayer(),
                                                     event->getMoveTo());
        case Event::event_shoot:
            return std::make_unique<ShootCommand>(event->getIdPlayer());
        case Event::event_stop_shoot:
            return std::make_unique<StopShootCommand>(event->getIdPlayer());
        case Event::event_throw_smoke:
            return std::make_unique<SmokeGrenadeCommand>(event->getIdPlayer());
        case Event::event_stop_smoke:
            return std::make_unique<StopSmokeGrenadeCommand>(event->getIdPlayer());
        case Event::event_throw_grenade:
            return std::make_unique<ExplosiveGrenadeCommand>(event->getIdPlayer());
        case Event::event_stop_grenade:
            return std::make_unique<StopExplosiveGrenadeCommand>(event->getIdPlayer());
        case Event::event_blitz_atack:
            return std::make_unique<BlitzAtackCommand>(event->getIdPlayer());
        case Event::event_recharge:
            return std::make_unique<ReloadCommand>(event->getIdPlayer());
        case Event::event_leave:
            return std::make_unique<LeaveCommand>(event->getIdPlayer());
        case Event::event_reanimate:
            return std::make_unique<ReanimateCommand>(event->getIdPlayer());
        case Event::event_cheat_finish_game:
            return std::make_unique<CheatFinishGameCommand>(event->getIdPlayer());
        case Event::event_cheat_more_velocity:
            return std::make_unique<CheatSuperSpeedCommand>(event->getIdPlayer());
        case Event::event_cheat_kill_enemies:
            return std::make_unique<CheatKillEnemiesCommand>(event->getIdPlayer());
        default:
            return nullptr;
    }
}
