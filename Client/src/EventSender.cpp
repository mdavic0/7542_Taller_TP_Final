#include "EventSender.h"
#include "Liberror.h"

EventSender::EventSender(Queue<std::shared_ptr<EventDTO>> &sdl_events,
                         ClientProtocol &protocol, bool& endGame) :
        sdl_events(sdl_events), protocol(protocol), talking(true), alive(true),
        endGame(endGame) {
}

void EventSender::run() {
    while (talking) {
        try {
            std::shared_ptr<EventDTO> response = sdl_events.pop();
            protocol.sendEvent(*response);
        } catch (ClosedQueue &exc) {
            talking = false;
            break;
        }
    }
    alive = false;
    std::cout << "termine sender\n";
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
