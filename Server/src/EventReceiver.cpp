#include "EventReceiver.h"
#include <utility>
#include "common_liberror.h"

EventReceiver::EventReceiver(Socket&& skt, GamesController& controller) :
    protocol(std::move(skt)), event_queue(),
    snapshot_queue(100), sender(protocol, snapshot_queue),
    controller(controller), game(0), talking(true), alive(true) {
}

void EventReceiver::run() {
    sender.start();
    while (talking) {
        try {
            EventDTO* eventDto = new EventDTO(protocol.getEvent());
            Event event = eventDto->getEvent();
            std::cout << "EventReceiver recibio un evento" << std::endl;
            if (event == Event::event_create) {
                std::cout << "El evento es: create" << std::endl;
                game = controller.create(eventDto, &snapshot_queue);
                this->event_queue = controller.get_event_queue(game);
                std::cout << "EventReceiver pushea evento a la queue" << std::endl;
                event_queue->push(eventDto);
            } else if (event == Event::event_join) {
                uint32_t code = eventDto->getN();
                uint8_t join_result = controller.try_join_game(eventDto, &snapshot_queue);
                if (join_result == 0) {
                    game = code;
                }
                this->event_queue = controller.get_event_queue(game);
                event_queue->push(eventDto);
            } else if (event == Event::event_move) {
                event_queue->push(eventDto);
            } else {
                talking = false;
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
