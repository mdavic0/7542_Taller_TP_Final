#ifndef COMMON_COMMANDDTO_H_
#define COMMON_COMMANDDTO_H_

#include "common_command.h"
#include <string>

class CommandDTO {
    private:
        Command command;
        std::string str;
        uint32_t n;

    public:
        explicit CommandDTO(
            Command command, const std::string& str, uint32_t n);

        Command getCommand() const;

        std::string getStr() const;

        uint32_t getN() const;

        /*
         * No queremos permitir que alguien haga copias
         */
         CommandDTO(const CommandDTO&) = delete;
         CommandDTO& operator=(const CommandDTO&) = delete;

         CommandDTO(CommandDTO&&);
         CommandDTO& operator=(CommandDTO&&);
};

#endif  // COMMON_COMMANDDTO_H_
