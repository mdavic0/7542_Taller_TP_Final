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

        static int p90_damage;
        static int p90_health;
        static int p90_velocity;
        static int p90_rate;
        static int p90_capacity;
        static int p90_injure;

        static int scout_damage;
        static int scout_health;
        static int scout_velocity;
        static int scout_rate;
        static int scout_capacity;
        static int scout_injure;
        
        static int grenade_damage;
        static int grenade_recharge;

        static int smoke_damage;
        static int smoke_recharge;
        
        static int blitz_damage;
        static int blitz_recharge;
        
        Configuration();
        ~Configuration();
        static void loadConfiguration(const std::string& filename);
};

#endif
