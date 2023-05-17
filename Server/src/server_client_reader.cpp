#include "server_client_reader.h"
#include <utility>
#include "common_liberror.h"

ClientReader::ClientReader(Socket&& skt, GamesController& controller) :
    protocol(std::move(skt)), q(100), writer(&this->protocol, &this->q),
    controller(controller), game(-1), talking(true), alive(true) {
    writer.start();
}

void ClientReader::run() {
    CommandDTO commanddto(Command::command_invalid, "", 0);

    while ((commanddto = protocol.getCommandDTO()).getCommand() != Command::command_invalid
        && talking) {
        try {
            Command command = commanddto.getCommand();

            if (command == Command::command_create) {
                game = controller.create(commanddto, &q);
                ResponseDTO *response = new ResponseDTO(command, game, 0,  "");
                q.push(response);
            } else if (command == Command::command_join) {
                uint32_t code = commanddto.getN();
                uint8_t ok = controller.join(commanddto, &q);
                if (ok == 0x00) {
                    game = code;
                }
                ResponseDTO *response = new ResponseDTO(command, code, ok,  "");
                q.push(response);
            } else if (command == Command::command_broadcast) {
                controller.broadcast(game, commanddto);
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
