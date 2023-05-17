#include "common_responsedto.h"
#include <string>
#include <iostream>
#include <sstream>

ResponseDTO::ResponseDTO(Command command, uint32_t code, uint8_t ok,  const std::string& str) :
    command(command), code(code), ok(ok), str(str) {}

Command ResponseDTO::getCommand() const {
    return command;
}

uint32_t ResponseDTO::getCode() const {
    return code;
}

uint8_t ResponseDTO::getOk() const {
    return ok;
}

std::string ResponseDTO::getStr() const {
    return str;
}

void ResponseDTO::print(const bool& showBroadcast) const {
    std::ostringstream print;

    if (command == Command::command_create) {
        print << "Created match: " << code << "\n";
    } else if (command == Command::command_join) {
        if (ok == 0x00) {
            print << "Joined to match: " << code << "\n";
        } else if (ok == 0x01) {
            print << "Match does not exist: " << code << "\n";
        }
    } else if (command == Command::command_broadcast && showBroadcast) {
        print << "Broadcasted: " << str << "\n";
    } else if (command == Command::command_read) {
        std::istringstream auxss(str);
        for (uint32_t i = 0; i < code; i++) {     // code is used as n, same type
            std::string auxstr;
            auxss >> auxstr;
            print << "Broadcasted: " << auxstr << "\n";
        }
    }
    std::string endPrint = print.str();
    if (endPrint.size() > 0) {
        std::cout << print.str();
    }
    return;
}

ResponseDTO::ResponseDTO(ResponseDTO&& other) {
    this->command = other.command;
    this->code = other.code;
    this->ok = other.ok;
    this->str = other.str;

    other.command = Command::command_invalid;
    other.code = 0;
    other.ok = 0;
    other.str = "";
}

ResponseDTO& ResponseDTO::operator=(ResponseDTO&& other) {
    if (this == &other)
        return *this;

    this->command = other.command;
    this->code = other.code;
    this->ok = other.ok;
    this->str = other.str;

    other.command = Command::command_invalid;
    other.code = 0;
    other.ok = 0;
    other.str = "";

    return *this;
}
