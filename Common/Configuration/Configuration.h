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
        /******************************
         * OPERATORS
         ******************************/
        // IDF:
        static int idf_damage;
        static int idf_health;
        static int idf_velocity;
        static int idf_rate;
        static int idf_capacity;
        static int idf_injure;
        static double idf_reload_time;
        static double idf_rate_time;
        static double idf_burst_delay;
        static float idf_scope;

        // P90:
        static int p90_damage;
        static int p90_health;
        static int p90_velocity;
        static int p90_rate;
        static int p90_capacity;
        static int p90_injure;
        static double p90_reload_time;
        static double p90_rate_time;
        static double p90_burst_delay;
        static float p90_scope;

        // SCOUT:
        static int scout_damage;
        static int scout_health;
        static int scout_velocity;
        static int scout_rate;
        static int scout_capacity;
        static int scout_injure;
        static double scout_reload_time;
        static double scout_rate_time;
        static double scout_burst_delay;
        static float scout_scope;
        static float scout_damage_decrease_by_enemy;

        // Special abilties
        static int grenade_damage;
        static int grenade_recharge;

        static int smoke_damage;
        static int smoke_recharge;
        
        static int blitz_damage;
        static int blitz_recharge;

        /*****************************
         * INFECTED
         ****************************/
        // Zombie:
        static int zombie_damage;
        static int zombie_health;
        static int zombie_velocity;

        // Jumper
        static int jumper_damage;
        static int jumper_health;
        static int jumper_velocity;

        // Witch
        static int witch_damage;
        static int witch_health;
        static int witch_velocity;

        // Spear
        static int spear_damage;
        static int spear_health;
        static int spear_velocity;

        // Venom
        static int venom_damage;
        static int venom_health;
        static int venom_velocity;

        /*********************************
         * Game Difficulty
         *******************************/
        // Easy
        static int zombie_amount_easy;
        static int jumper_amount_easy;
        static int witch_amount_easy;
        static int spear_amount_easy;
        static int venom_amount_easy;

        // Normal
        static int zombie_amount_normal;
        static int jumper_amount_normal;
        static int witch_amount_normal;
        static int spear_amount_normal;
        static int venom_amount_normal;

        // Hard
        static int zombie_amount_hard;
        static int jumper_amount_hard;
        static int witch_amount_hard;
        static int spear_amount_hard;
        static int venom_amount_hard;

        // God
        static int zombie_amount_god;
        static int jumper_amount_god;
        static int witch_amount_god;
        static int spear_amount_god;
        static int venom_amount_god;


        Configuration();
        ~Configuration();
        static void loadConfiguration(const std::string& filename);
};

#endif
