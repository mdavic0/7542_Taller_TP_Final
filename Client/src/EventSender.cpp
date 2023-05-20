#include "EventSender.h"
#include "common_liberror.h"

EventSender::EventSender(Queue<EventDTO*> &sdl_events, ClientProtocol &protocol) :
        sdl_events(sdl_events), protocol(protocol), talking(true), alive(true) {}

void EventSender::run() {
    while (talking) {
        try {
            EventDTO* response = sdl_events.pop();
            protocol.sendEvent(*response);
            delete response;
        } catch (const ClosedQueue&) {
            break;
        } catch (const LibError& err) {
            // socket closed
        }
    }
    alive = false;
}

void EventSender::stop() {
    talking = false;
}

bool EventSender::ended() {
    return !alive;
}

EventSender::~EventSender() {
    join();
}