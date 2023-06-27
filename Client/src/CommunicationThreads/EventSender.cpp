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
            protocol.sendEvent(response, skt);
        } catch (const ClosedQueue &exc) {      // sql quit 1, server ends q and slow client 2
            skt->shutdown(2);
            skt->close();
            break;
        } catch (const LibError &exc) {
            sdl_events.close();
            break;
        } catch (const std::exception& exc) {
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
