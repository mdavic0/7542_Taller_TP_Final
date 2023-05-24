#include "EventReceiver.h"
#include <utility>
#include "common_liberror.h"

EventReceiver::EventReceiver(Socket&& skt, GamesController& controller) :
    protocol(std::move(skt)), event_queue(),
    snapshot_queue(100), sender(protocol, snapshot_queue),
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
                event_queue->push(eventDto);
            } else if (event == Event::event_join) {
                uint32_t code = eventDto->getN();
                uint8_t join_result;
                this->event_queue = controller.try_join_game(eventDto,
                                                             &snapshot_queue,
                                                             join_result);
                if (join_result == 0) {
                    game_code = code;
                    event_queue->push(eventDto);
                }
            } else if (event == Event::event_move) {
                event_queue->push(eventDto);
            } else {
                talking = false; // TODO: Analizar bien las condiciones de corte
            }
        } catch (const LibError& err) {
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
