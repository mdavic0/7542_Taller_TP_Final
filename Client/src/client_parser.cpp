#include "client_parser.h"
#include <string>
#include <utility>
#include <iostream>
#include <sstream>

Parser::Parser() {}

EventDTO Parser::getNextCommand() {
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "create") {
        std::string scenario;
        iss >> scenario;
        return EventDTO(Event::event_create, MoveTo::move_not, scenario, 0);
    } else if (command == "join") {
        uint32_t code;
        iss >> code;
        return EventDTO(Event::event_join, MoveTo::move_not,"", code);
    } else if (command == "broadcast") {
        std::string msg;
        iss >> msg;
        return EventDTO(Event::event_broadcast, MoveTo::move_not,msg, 0);
    } else if (command == "read") {
        uint32_t n;
        iss >> n;
        return EventDTO(Event::event_read, MoveTo::move_not,"", n);
    } else if (command == "leave") {
        return EventDTO(Event::event_leave, MoveTo::move_not,"", 0);
    } else {
        return EventDTO(Event::event_invalid, MoveTo::move_not,"", 0);
    }
}
