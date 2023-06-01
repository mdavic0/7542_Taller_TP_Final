#ifndef ST_OPERATOR_H_
#define ST_OPERATOR_H_

#include "TypeOperator.h"
#include <utility>

struct StOperator
{
    TypeOperator type;
    std::pair<int, int> position;
    int id;
    int health;
    
};


#endif
