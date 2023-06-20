#include "EventSender.h"
#include "Liberror.h"

EventSender::EventSender(Queue<std::shared_ptr<EventDTO>> &sdl_events,
                         std::shared_ptr<Socket> skt, bool& endGame) :
        sdl_events(sdl_events), skt(skt), talking(true), alive(true),
        endGame(endGame) {
}

void EventSender::run() {
    while (talking) {
        try {
            std::shared_ptr<EventDTO> response = sdl_events.pop();
            protocol.sendEvent(*response, skt);
        } catch (ClosedQueue &exc) {
            talking = false;
            //protocol.stop();
            skt->shutdown(2);
            skt->close();
        } catch (const LibError &exc) {
            talking = false;
        } catch (...) {}
    }
    alive = false;
}

void EventSender::stop() {
    talking = false;
    sdl_events.close();
}

bool EventSender::ended() {
    return !alive;
}

EventSender::~EventSender() {
    join();
}
