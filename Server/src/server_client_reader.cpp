#include "server_client_reader.h"
#include <utility>
#include "common_liberror.h"

ClientReader::ClientReader(Socket&& skt, GamesController& controller) :
    protocol(std::move(skt)), q(100), writer(&this->protocol, &this->q),
    controller(controller), game(-1), talking(true), alive(true) {
    writer.start();
}

void ClientReader::run() {
    EventDTO eventDto(Event::event_invalid, MoveTo::move_not, "", 0);

    while ((eventDto = protocol.getEvent()).getEvent() != Event::event_invalid
        && talking) {
        try {
            Event event = eventDto.getEvent();

            if (event == Event::event_create) {
                game = controller.create(eventDto, &q);
                Snapshot *response = new Snapshot(event, game, 0, "");
                q.push(response);
            } else if (event == Event::event_join) {
                uint32_t code = eventDto.getN();
                uint8_t ok = controller.join(eventDto, &q);
                if (ok == 0x00) {
                    game = code;
                }
                Snapshot *response = new Snapshot(event, game, 0, "");
                q.push(response);
            } else if (event == Event::event_broadcast) {
                controller.broadcast(game, eventDto);
            }
        } catch (const LibError& err) {
            // socket closed
            break;
        }
    }
    alive = false;
}

void ClientReader::stop() {
    talking = false;
    protocol.stop();
}

bool ClientReader::ended() {
    return !alive;
}

ClientReader::~ClientReader() {
    q.close();
    writer.stop();
    join();
}
