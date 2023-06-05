#ifndef CONFIG_H_
#define CONFIG_H_

#include <yaml-cpp/yaml.h>
#include <string>
#include <fstream>
#include <map>
#include "StructOperator.h"

class Config {
private:
    std::ifstream file;
    std::string filename;
    YAML::Node config;
    std::map<int, Operator> listOperator;
    std::map<std::string, Skill> listSkill;
    void loadConfig();
    void readFile();
public:
    explicit Config(const std::string& filename);
    ~Config();
    Operator getOperator(int id);
};

#endif
