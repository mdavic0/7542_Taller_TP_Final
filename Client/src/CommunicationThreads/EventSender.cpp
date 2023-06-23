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
        } catch (const ClosedQueue &exc) {
            skt->shutdown(2);
            skt->close();
            std::cout << "Client event Queue closed, then socket is closed " << std::endl;
            break;
        } catch (const LibError &exc) {
            sdl_events.close();
            std::cout << "Client event sender closed, then events Queue is closed too " << std::endl;
            break;
        } catch (const std::exception& exc) {
            std::cout << "EventSender - Exception occurred test log: " << exc.what() << std::endl;
        }
    }
    alive = false;
}

void EventSender::stop() {
    talking = false;
    skt->shutdown(2);
    skt->close();
}

bool EventSender::ended() {
    return !alive;
}

EventSender::~EventSender() {
    join();
}
