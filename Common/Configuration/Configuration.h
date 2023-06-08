#ifndef CONFIG_H_
#define CONFIG_H_

#include <yaml-cpp/yaml.h>
#include <string>
#include <map>

class Configuration;

typedef Configuration CF;

class Configuration {
    public:
        static YAML::Node file;
        static int idf_damage;
        static int idf_health;
        static int idf_velocity;
        static int idf_rate;
        static int idf_capacity;
        static int idf_injure;
                // static OperatorConfig p90;
        // static OperatorConfig scout;
        // static std::map<std::string, Skill> listSkill;
        Configuration();
        ~Configuration();
        static void loadConfiguration(const std::string& filename);
};

#endif
