#ifndef COMMON_RESPONSEDTO_H_
#define COMMON_RESPONSEDTO_H_

#include "common_command.h"
#include <string>

class ResponseDTO {
        Command command;
        uint32_t code;
        uint8_t ok;
        std::string str;

    public:
        explicit ResponseDTO(
            Command command, uint32_t code, uint8_t ok,  const std::string& str);

        Command getCommand() const;

        uint32_t getCode() const;

        uint8_t getOk() const;

        std::string getStr() const;

        void print(const bool& showBroadcast) const;

        /*
         * No queremos permitir que alguien haga copias
         */
         ResponseDTO(const ResponseDTO&) = delete;
         ResponseDTO& operator=(const ResponseDTO&) = delete;

         ResponseDTO(ResponseDTO&&);
         ResponseDTO& operator=(ResponseDTO&&);
};

#endif  // COMMON_RESPONSEDTO_H_
