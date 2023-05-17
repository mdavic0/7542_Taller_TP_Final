#include "common_commanddto.h"

CommandDTO::CommandDTO(Command command, const std::string& str, uint32_t n):
    command(command), str(str), n(n) {}

Command CommandDTO::getCommand() const {
    return command;
}

std::string CommandDTO::getStr() const {
    return str;
}

uint32_t CommandDTO::getN() const {
    return n;
}

CommandDTO::CommandDTO(CommandDTO&& other) {
    this->command = other.command;
    this->str = other.str;
    this->n = other.n;

    other.command = Command::command_invalid;
    other.str = "";
    other.n = 0;
}

CommandDTO& CommandDTO::operator=(CommandDTO&& other) {
    if (this == &other)
        return *this;

    this->command = other.command;
    this->str = other.str;
    this->n = other.n;

    other.command = Command::command_invalid;
    other.str = "";
    other.n = 0;

    return *this;
}
