#ifndef MATCH_H_
#define MATCH_H_

#include <list>
#include "StOperator.h"

class Match {
    private:
        std::list<StOperator> players;
        int mapId;
        int mode;
    public:
        Match() = default;
        ~Match() = default;
};

#endif
