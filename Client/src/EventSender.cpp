#include "EventSender.h"
#include "Liberror.h"

EventSender::EventSender(Queue<EventDTO*> &sdl_events,
    ClientProtocol &protocol, bool& endGame) :
    sdl_events(sdl_events), protocol(protocol), talking(true), alive(true),
    endGame(endGame) {
}

void EventSender::run() {
    while (talking) {
        try {
            EventDTO* response = sdl_events.pop();
            if (response != nullptr) {
                protocol.sendEvent(*response);
                delete response;
            }
        } catch (ClosedQueue &exc) {
            std::cerr << exc.what() << std::endl;
            talking = false;
            break;
        } // catch (const LibError& err) {
        //     talking = false;
        //     // socket closed
        // }
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