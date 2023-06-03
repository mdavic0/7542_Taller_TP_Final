#ifndef ST_OPERATOR_H_
#define ST_OPERATOR_H_

#include "TypeOperator.h"
#include <utility>
#include <map>
#include <string>

struct Operator {
    TypeOperator type;
    int damage;
    int health;
    int velocity;
    int rate;
    int capacity;
    std::map<std::string, Skill> skills;
    int injure;
    
};

struct Skill {
    int damage;
    int recharge;
};


#endif
