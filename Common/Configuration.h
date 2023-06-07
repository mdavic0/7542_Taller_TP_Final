#ifndef CONFIG_H_
#define CONFIG_H_

#include <yaml-cpp/yaml.h>
#include <string>
#include <fstream>
#include <map>
#include "StructOperator.h"

class Configuration {
    private:
        static YAML::Node file;
        static std::map<int, Operator> listOperator;
        static std::map<std::string, Skill> listSkill;
    public:
        Configuration();
        ~Configuration();
        static void loadConfiguration(const std::string& filename);
};

#endif
