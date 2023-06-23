#include "EventReceiver.h"
#include <utility>
#include "Liberror.h"

EventReceiver::EventReceiver(std::shared_ptr<Socket> skt, GamesController& controller) :
    skt(skt), protocol(), event_queue(),
    snapshot_queue(1000), sender(this->skt, snapshot_queue),
    controller(controller), game_code(0), talking(true), alive(true) {
}

void EventReceiver::run() {
    sender.start();
    while (talking) {
        try {
            std::shared_ptr<EventDTO> eventDto = std::make_shared<EventDTO>(protocol.getEvent(skt));
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
        } catch (const LibError& exc) {
            std::cout << "EventReceiver - socket closed " << std::endl;
            break;
        }  catch (const std::exception& exc) {
            std::cout << "EventReceiver - Exception occurred test log: " << exc.what() << std::endl;
            break;
        }
    }
    alive = false;
    snapshot_queue.close();
}

void EventReceiver::stop() {
    std::cout << "EventReceiver - stop " << std::endl;
    if (alive == true) {
        skt->shutdown(2);
        skt->close();
        talking = false;
    }
    sender.stop();
    std::cout << "EventReceiver - end stop " << std::endl;
}

bool EventReceiver::ended() {
    return !alive;
}

EventReceiver::~EventReceiver() {
    std::cout << "EventReceiver - delete " << std::endl;
    join();
}
