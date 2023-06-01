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
                event_queue->push(eventDto); // TODO: NO PUSHEAR DIRECTAMENTE
            } else if (event == Event::event_join) {
                uint32_t code = eventDto->getN();
                uint8_t join_result;
                this->event_queue = controller.try_join_game(eventDto,
                                                             &snapshot_queue,
                                                             join_result);
                if (join_result == 0) {
                    game_code = code;
                    event_queue->push(eventDto);
                } else {
                    snapshot_queue.push(new Snapshot(Event(JOIN_CODE), join_result));
                }
            } else if (event == Event::event_start_game) {
                event_queue->push(eventDto);
            } else if (event == Event::event_move || event == Event::event_stop_move) {
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
