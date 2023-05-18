#include "client_client.h"
#include "client_parser.h"
#include "common_liberror.h"

Client::Client(const std::string& hostname, const std::string& servname) :
    protocol(Socket(hostname.c_str(), servname.c_str())) {}

void Client::run() {
    Parser parser;
    EventDTO eventDto(Event::event_invalid, MoveTo::move_not,"", 0);
    while ((eventDto = parser.getNextCommand()).getEvent() != Event::event_invalid
        && eventDto.getEvent() != Event::event_leave) {
        protocol.sendEvent(eventDto);
        Snapshot response(eventDto.getEvent(), 0,0, eventDto.getStr());
        response.print(true);
    }

    if (eventDto.getEvent() == Event::event_invalid) {
        throw LibError(-1 , "input of invalid command");
    }
}
