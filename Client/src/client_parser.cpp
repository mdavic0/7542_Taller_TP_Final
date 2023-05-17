#include "client_parser.h"
#include <string>
#include <utility>
#include <iostream>
#include <sstream>

Parser::Parser() {}

CommandDTO Parser::getNextCommand() {
    std::string line;
    std::getline(std::cin, line);

    std::istringstream iss(line);
    std::string command;
    iss >> command;

    if (command == "create") {
        std::string scenario;
        iss >> scenario;
        return std::move(CommandDTO(Command::command_create, scenario, 0));
    } else if (command == "join") {
        uint32_t code;
        iss >> code;
        return std::move(CommandDTO(Command::command_join, "", code));
    } else if (command == "broadcast") {
        std::string msg;
        iss >> msg;
        return std::move(CommandDTO(Command::command_broadcast, msg, 0));
    } else if (command == "read") {
        uint32_t n;
        iss >> n;
        return std::move(CommandDTO(Command::command_read, "", n));
    } else if (command == "leave") {
        return std::move(CommandDTO(Command::command_leave, "", 0));
    } else {
        return std::move(CommandDTO(Command::command_invalid, "", 0));
    }
}
