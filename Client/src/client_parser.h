#ifndef CLIENT_PARSER_H_
#define CLIENT_PARSER_H_

#include "common_eventdto.h"

/*
 * TDA Parser
 * Transforma la entrada a objetos CommandDTO.
 */
class Parser {
    public:
        Parser();

        /*
         * Método utilizado para obtener el siguinete comando.
         */
        EventDTO getNextCommand();
};

#endif  // CLIENT_PARSER_H_
