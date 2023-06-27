#include "EventReceiver.h"
#include <utility>
#include "Liberror.h"

EventReceiver::EventReceiver(std::shared_ptr<Socket> skt, GamesController& controller) :
    skt(skt), protocol(), event_queue(nullptr),
    snapshot_queue(1000), sender(this->skt, snapshot_queue),
    controller(controller), game(nullptr), talking(true), alive(true) {
}

void EventReceiver::run() {
    sender.start();
    while (talking) {
        try {
            while (!game) {
                std::shared_ptr<EventDTO> eventDto = std::make_shared<EventDTO>(protocol.getEvent(skt));
                Event event = eventDto->getEvent();
                if (event == Event::event_create) {
                    this->event_queue = controller.create(eventDto,
                                                          &snapshot_queue,
                                                          game);

                } else if (event == Event::event_join) {
                    this->event_queue = controller.try_join_game(eventDto,
                                                                &snapshot_queue,
                                                                game);
                } else if (event == Event::event_leave) {
                    snapshot_queue.close();
                }
            }

            while (!game->running()) {
                std::shared_ptr<EventDTO> eventDto = std::make_shared<EventDTO>(protocol.getEvent(skt));
                Event event = eventDto->getEvent();
                if (event == Event::event_start_game && game != nullptr) {
                    game->startGame();

                } else if (event == Event::event_leave && game != nullptr) {
                    game->clientLeave(&snapshot_queue);

                }
            }

            while (game->running()) {
                std::shared_ptr<EventDTO> eventDto = std::make_shared<EventDTO>(protocol.getEvent(skt));
                event_queue->push(eventDto);
            }


        } catch (const LibError& exc) {     // client slow, quit sdl, server ends whit q input
            break;
        }  catch (const std::exception& exc) {
            break;
        }
    }
    alive = false;
}

void EventReceiver::stop() {
    talking = false;
    if (!sender.ended()) {      // server ended with q
        snapshot_queue.close();
    }
}

bool EventReceiver::ended() {
    return !alive;
}

EventReceiver::~EventReceiver() {
    join();
}
