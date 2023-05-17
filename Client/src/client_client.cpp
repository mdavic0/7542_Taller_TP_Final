#include "client_client.h"
#include "client_parser.h"
#include "common_liberror.h"

Client::Client(const std::string& hostname, const std::string& servname) :
    protocol(hostname, servname) {}

void Client::run() {
    Parser parser;
    CommandDTO command(Command::command_invalid, "", 0);
    while ((command = parser.getNextCommand()).getCommand() != Command::command_invalid
        && command.getCommand() != Command::command_leave) {
        ResponseDTO response = protocol.sendCommand(command);
        response.print(true);
    }

    if (command.getCommand() == Command::command_invalid) {
        throw LibError(-1 , "input of invalid command");
    }
}
