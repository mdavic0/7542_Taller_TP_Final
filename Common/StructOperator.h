#ifndef STRUCTOPERATOR_H_
#define STRUCTOPERATOR_H_

#include "TypeOperator.h"
#include <map>
#include <string>

struct Skill {
    int damage;
    int recharge;
};

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

#endif
