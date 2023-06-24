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
            std::cout << "Client event Queue closed" << std::endl;
            break;
        } catch (const LibError &exc) {
            sdl_events.close();
            std::cout << "Client event sender closed" << std::endl;
            break;
        } catch (const std::exception& exc) {
            std::cout << "EventSender - Exception occurred test log: " << exc.what() << std::endl;
        }
    }
    alive = false;
}

void EventSender::stop() {
    std::cout << "EventSender - stop " << std::endl;
    talking = false;
    std::cout << "EventSender - end stop " << std::endl;
}

bool EventSender::ended() {
    return !alive;
}

EventSender::~EventSender() {    
    std::cout << "EventSender - delete " << std::endl;
    join();
}
