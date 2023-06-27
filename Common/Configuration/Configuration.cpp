#include "Configuration.h"
#include <iostream>
#include "Exception.h"
#include "Defines.h"

YAML::Node CF::file = YAML::LoadFile(PATH);

/******************************
* OPERATORS
******************************/
double CF::fell_down_death_time = CF::file["fell_down_death_time"].as<double>();
// IDF:
int CF::idf_damage = CF::file["idf_damage"].as<int>();
int CF::idf_health = CF::file["idf_health"].as<int>();
int CF::idf_velocity = CF::file["idf_velocity"].as<int>();
int CF::idf_rate = CF::file["idf_rate"].as<int>();
int CF::idf_capacity = CF::file["idf_capacity"].as<int>();
int CF::idf_injure = CF::file["idf_injure"].as<int>();
double CF::idf_reload_time = CF::file["idf_reload_time"].as<double>();
double CF::idf_rate_time = CF::file["idf_rate_time"].as<double>();
double CF::idf_burst_delay = CF::file["idf_burst_delay"].as<double>();
float CF::idf_scope = CF::file["idf_scope"].as<float>();

// P90:
int CF::p90_damage = CF::file["p90_damage"].as<int>();
int CF::p90_health = CF::file["p90_health"].as<int>();
int CF::p90_velocity = CF::file["p90_velocity"].as<int>();
int CF::p90_rate = CF::file["p90_rate"].as<int>();
int CF::p90_capacity = CF::file["p90_capacity"].as<int>();
int CF::p90_injure = CF::file["p90_injure"].as<int>();
double CF::p90_reload_time = CF::file["p90_reload_time"].as<double>();
double CF::p90_rate_time = CF::file["p90_rate_time"].as<double>();
double CF::p90_burst_delay = CF::file["p90_burst_delay"].as<double>();
float CF::p90_scope = CF::file["p90_scope"].as<float>();

// SCOUT:
int CF::scout_damage = CF::file["scout_damage"].as<int>();
int CF::scout_health = CF::file["scout_health"].as<int>();
int CF::scout_velocity = CF::file["scout_velocity"].as<int>();
int CF::scout_rate = CF::file["scout_rate"].as<int>();
int CF::scout_capacity = CF::file["scout_capacity"].as<int>();
int CF::scout_injure = CF::file["scout_injure"].as<int>();
double CF::scout_reload_time = CF::file["scout_reload_time"].as<double>();
double CF::scout_rate_time = CF::file["scout_rate_time"].as<double>();
double CF::scout_burst_delay = CF::file["scout_burst_delay"].as<double>();
float CF::scout_scope = CF::file["scout_scope"].as<float>();
float CF::scout_damage_decrease_by_enemy = CF::file["scout_damage_decrease_by_enemy"].as<float>();

/******************************
* Special abilities
******************************/
double CF::stop_skill_time = CF::file["stop_skill_time"].as<double>();
int CF::grenade_velocity = CF::file["grenade_velocity"].as<int>();

// Grenade
int CF::grenade_damage = CF::file["grenade_damage"].as<int>();
int CF::grenade_recharge = CF::file["grenade_recharge"].as<int>();
double CF::grenade_explosion_time = CF::file["grenade_explosion_time"].as<double>();

// Smoke
int CF::smoke_damage = CF::file["smoke_damage"].as<int>();
int CF::smoke_recharge = CF::file["smoke_recharge"].as<int>();
double CF::smoke_explosion_time = CF::file["smoke_explosion_time"].as<double>();
double CF::smoke_speed_reduction = CF::file["smoke_speed_reduction"].as<double>();

// Blitz
int CF::blitz_damage = CF::file["blitz_damage"].as<int>();
int CF::blitz_recharge = CF::file["blitz_recharge"].as<int>();
double CF::blitz_animation_time = CF::file["blitz_animation_time"].as<double>();

/*****************************
* INFECTED
****************************/
// Zombie:
int CF::zombie_damage = CF::file["zombie_damage"].as<int>();
int CF::zombie_health = CF::file["zombie_health"].as<int>();
int CF::zombie_velocity = CF::file["zombie_velocity"].as<int>();

// Jumper
int CF::jumper_damage = CF::file["jumper_damage"].as<int>();
int CF::jumper_health = CF::file["jumper_health"].as<int>();
int CF::jumper_velocity = CF::file["jumper_velocity"].as<int>();

// Witch
int CF::witch_damage = CF::file["witch_damage"].as<int>();
int CF::witch_health = CF::file["witch_health"].as<int>();
int CF::witch_velocity = CF::file["witch_velocity"].as<int>();

// Spear
int CF::spear_damage = CF::file["spear_damage"].as<int>();
int CF::spear_health = CF::file["spear_health"].as<int>();
int CF::spear_velocity = CF::file["spear_velocity"].as<int>();

// Venom
int CF::venom_damage = CF::file["venom_damage"].as<int>();
int CF::venom_health = CF::file["venom_health"].as<int>();
int CF::venom_velocity = CF::file["venom_velocity"].as<int>();

/*********************************
 * Game Difficulty
 *******************************/
// Easy
int CF::zombie_amount_easy = CF::file["zombie_amount_easy"].as<int>();
int CF::jumper_amount_easy = CF::file["jumper_amount_easy"].as<int>();
int CF::witch_amount_easy = CF::file["witch_amount_easy"].as<int>();
int CF::spear_amount_easy = CF::file["spear_amount_easy"].as<int>();
int CF::venom_amount_easy = CF::file["venom_amount_easy"].as<int>();

// Normal
int CF::zombie_amount_normal = CF::file["zombie_amount_normal"].as<int>();
int CF::jumper_amount_normal = CF::file["jumper_amount_normal"].as<int>();
int CF::witch_amount_normal = CF::file["witch_amount_normal"].as<int>();
int CF::spear_amount_normal = CF::file["spear_amount_normal"].as<int>();
int CF::venom_amount_normal = CF::file["venom_amount_normal"].as<int>();

// Hard
int CF::zombie_amount_hard = CF::file["zombie_amount_hard"].as<int>();
int CF::jumper_amount_hard = CF::file["jumper_amount_hard"].as<int>();
int CF::witch_amount_hard = CF::file["witch_amount_hard"].as<int>();
int CF::spear_amount_hard = CF::file["spear_amount_hard"].as<int>();
int CF::venom_amount_hard = CF::file["venom_amount_hard"].as<int>();

// God
int CF::zombie_amount_god = CF::file["zombie_amount_god"].as<int>();
int CF::jumper_amount_god = CF::file["jumper_amount_god"].as<int>();
int CF::witch_amount_god = CF::file["witch_amount_god"].as<int>();
int CF::spear_amount_god = CF::file["spear_amount_god"].as<int>();
int CF::venom_amount_god = CF::file["venom_amount_god"].as<int>();

Configuration::Configuration() {
}

void Configuration::loadConfiguration(const std::string& filename) {
    file = YAML::LoadFile(filename);
    /******************************
    * OPERATORS
    ******************************/
    fell_down_death_time = file["fell_down_death_time"].as<double>();

    // IDF:
    idf_damage = file["idf_damage"].as<int>();
    idf_health = file["idf_health"].as<int>();
    idf_velocity = file["idf_velocity"].as<int>();
    idf_rate = file["idf_rate"].as<int>();
    idf_capacity = file["idf_capacity"].as<int>();
    idf_injure = file["idf_injure"].as<int>();
    idf_reload_time = file["idf_reload_time"].as<double>();
    idf_rate_time = file["idf_rate_time"].as<double>();
    idf_burst_delay = file["idf_burst_delay"].as<double>();

    // P90:
    p90_damage = file["p90_damage"].as<int>();
    p90_health = file["p90_health"].as<int>();
    p90_velocity = file["p90_velocity"].as<int>();
    p90_rate = file["p90_rate"].as<int>();
    p90_capacity = file["p90_capacity"].as<int>();
    p90_injure = file["p90_injure"].as<int>();
    p90_reload_time = file["p90_reload_time"].as<double>();
    p90_rate_time = file["p90_rate_time"].as<double>();
    p90_burst_delay = file["p90_burst_delay"].as<double>();

    // SCOUT:
    scout_damage = file["scout_damage"].as<int>();
    scout_health = file["scout_health"].as<int>();
    scout_velocity = file["scout_velocity"].as<int>();
    scout_rate = file["scout_rate"].as<int>();
    scout_capacity = file["scout_capacity"].as<int>();
    scout_injure = file["scout_injure"].as<int>();
    scout_reload_time = file["scout_reload_time"].as<double>();
    scout_rate_time = file["scout_rate_time"].as<double>();
    scout_burst_delay = file["scout_burst_delay"].as<double>();

    /******************************
     * Special abilities
     ******************************/
    stop_skill_time = file["stop_skill_time"].as<double>();
    grenade_velocity = file["grenade_velocity"].as<int>();

    // Grenade
    grenade_damage = file["grenade_damage"].as<int>();
    grenade_recharge = file["grenade_recharge"].as<int>();
    grenade_explosion_time = file["grenade_explosion_time"].as<double>();

    // Smoke
    smoke_damage = file["smoke_damage"].as<int>();
    smoke_recharge = file["smoke_recharge"].as<int>();
    smoke_explosion_time = file["smoke_explosion_time"].as<double>();
    smoke_speed_reduction = file["smoke_speed_reduction"].as<double>();

    // Blitz
    blitz_damage = file["blitz_damage"].as<int>();
    blitz_recharge = file["blitz_recharge"].as<int>();
    blitz_animation_time = file["blitz_animation_time"].as<double>();

    /*****************************
    * INFECTED
    *****************************/
    // Zombie:
    zombie_damage = file["zombie_damage"].as<int>();
    zombie_health = file["zombie_health"].as<int>();
    zombie_velocity = file["zombie_velocity"].as<int>();

    // Jumper
    jumper_damage = file["jumper_damage"].as<int>();
    jumper_health = file["jumper_health"].as<int>();
    jumper_velocity = file["jumper_velocity"].as<int>();

    // Witch
    witch_damage = file["witch_damage"].as<int>();
    witch_health = file["witch_health"].as<int>();
    witch_velocity = file["witch_velocity"].as<int>();

    // Spear
    spear_damage = file["spear_damage"].as<int>();
    spear_health = file["spear_health"].as<int>();
    spear_velocity = file["spear_velocity"].as<int>();

    // Venom
    venom_damage = file["venom_damage"].as<int>();
    venom_health = file["venom_health"].as<int>();
    venom_velocity = file["venom_velocity"].as<int>();

    /*********************************
    * Game Difficulty
    *******************************/
    // Easy
    zombie_amount_easy = file["zombie_amount_easy"].as<int>();
    jumper_amount_easy = file["jumper_amount_easy"].as<int>();
    witch_amount_easy = file["witch_amount_easy"].as<int>();
    spear_amount_easy = file["spear_amount_easy"].as<int>();
    venom_amount_easy = file["venom_amount_easy"].as<int>();

    // Normal
    zombie_amount_normal = file["zombie_amount_normal"].as<int>();
    jumper_amount_normal = file["jumper_amount_normal"].as<int>();
    witch_amount_normal = file["witch_amount_normal"].as<int>();
    spear_amount_normal = file["spear_amount_normal"].as<int>();
    venom_amount_normal = file["venom_amount_normal"].as<int>();

    // Hard
    zombie_amount_hard = file["zombie_amount_hard"].as<int>();
    jumper_amount_hard = file["jumper_amount_hard"].as<int>();
    witch_amount_hard = file["witch_amount_hard"].as<int>();
    spear_amount_hard = file["spear_amount_hard"].as<int>();
    venom_amount_hard = file["venom_amount_hard"].as<int>();

    // God
    zombie_amount_god = file["zombie_amount_god"].as<int>();
    jumper_amount_god = file["jumper_amount_god"].as<int>();
    witch_amount_god = file["witch_amount_god"].as<int>();
    spear_amount_god = file["spear_amount_god"].as<int>();
    venom_amount_god = file["venom_amount_god"].as<int>();
}

Configuration::~Configuration() = default;
