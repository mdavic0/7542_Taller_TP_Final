#include "EventReceiver.h"
#include <utility>
#include "common_liberror.h"

EventReceiver::EventReceiver(ServerProtocol &protocol, Queue<EventDTO *> &event_queue) :
    protocol(protocol), event_queue(event_queue), talking(true), alive(true) {}

void EventReceiver::run() {
    EventDTO eventDto(Event::event_invalid, MoveTo::move_not, "", 0);

    while (talking) {
        try {
            EventDTO* event = new EventDTO(protocol.getEvent());
            event_queue.push(event);
        } catch (const LibError& err) {
            // socket closed
            break;
        }
    }
    alive = false;
}

void EventReceiver::stop() {
    talking = false;
    // protocol.stop(); ???
}

bool EventReceiver::ended() {
    return !alive;
}

EventReceiver::~EventReceiver() {

}
