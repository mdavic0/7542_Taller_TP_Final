#include "EventReceiver.h"
#include <utility>
#include "Liberror.h"

EventReceiver::EventReceiver(Socket&& skt, GamesController& controller) :
    protocol(std::move(skt)), event_queue(),
    snapshot_queue(1000), sender(protocol, snapshot_queue),
    controller(controller), game_code(0), talking(true), alive(true) {
}

void EventReceiver::run() {
    sender.start();
    while (talking) {
        try {
            EventDTO* eventDto = new EventDTO(protocol.getEvent());
            Event event = eventDto->getEvent();
            if (event == Event::event_create) {
                this->event_queue = controller.create(eventDto,
                                                      &snapshot_queue,
                                                      game_code);

            } else if (event == Event::event_join) {
                this->event_queue = controller.try_join_game(eventDto,
                                                             &snapshot_queue);

            } else if (event == Event::event_start_game) {
                controller.startGame(game_code);

            } else {
                event_queue->push(eventDto);
            }
        } catch (const LibError& err) {
            talking = false; // TODO: Analizar bien las condiciones de corte
            // socket closed
            break;
        }
    }
    alive = false;
}

void EventReceiver::stop() {
    talking = false;
    protocol.stop();
}

bool EventReceiver::ended() {
    return !alive;
}

EventReceiver::~EventReceiver() {
    snapshot_queue.close();
    sender.stop();
    join();
}