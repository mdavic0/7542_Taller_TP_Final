#include "Configuration.h"
#include <iostream>
#include "Exception.h"
#include "Defines.h"

YAML::Node CF::file = YAML::LoadFile(PATH);

/******************************
* OPERATORS
******************************/
// IDF:
int CF::idf_damage = CF::file["idf_damage"].as<int>();
int CF::idf_health = CF::file["idf_health"].as<int>();
int CF::idf_velocity = CF::file["idf_velocity"].as<int>();
int CF::idf_rate = CF::file["idf_rate"].as<int>();
int CF::idf_capacity = CF::file["idf_capacity"].as<int>();
int CF::idf_injure = CF::file["idf_injure"].as<int>();

// P90:
int CF::p90_damage = CF::file["p90_damage"].as<int>();
int CF::p90_health = CF::file["p90_health"].as<int>();
int CF::p90_velocity = CF::file["p90_velocity"].as<int>();
int CF::p90_rate = CF::file["p90_rate"].as<int>();
int CF::p90_capacity = CF::file["p90_capacity"].as<int>();
int CF::p90_injure = CF::file["p90_injure"].as<int>();

// SCOUT:
int CF::scout_damage = CF::file["scout_damage"].as<int>();
int CF::scout_health = CF::file["scout_health"].as<int>();
int CF::scout_velocity = CF::file["scout_velocity"].as<int>();
int CF::scout_rate = CF::file["scout_rate"].as<int>();
int CF::scout_capacity = CF::file["scout_capacity"].as<int>();
int CF::scout_injure = CF::file["scout_injure"].as<int>();

// Special abilties
int CF::grenade_damage = CF::file["grenade_damage"].as<int>();
int CF::grenade_recharge = CF::file["grenade_recharge"].as<int>();
int CF::smoke_damage = CF::file["smoke_damage"].as<int>();
int CF::smoke_recharge = CF::file["smoke_recharge"].as<int>();
int CF::blitz_damage = CF::file["blitz_damage"].as<int>();
int CF::blitz_recharge = CF::file["blitz_recharge"].as<int>();

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

Configuration::Configuration() {
}

void Configuration::loadConfiguration(const std::string& filename) {
    file = YAML::LoadFile(filename);
    /******************************
    * OPERATORS
    ******************************/
    // IDF:
    idf_damage = file["idf_damage"].as<int>();
    idf_health = file["idf_health"].as<int>();
    idf_velocity = file["idf_velocity"].as<int>();
    idf_rate = file["idf_rate"].as<int>();
    idf_capacity = file["idf_capacity"].as<int>();
    idf_injure = file["idf_injure"].as<int>();

    // P90:
    p90_damage = file["p90_damage"].as<int>();
    p90_health = file["p90_health"].as<int>();
    p90_velocity = file["p90_velocity"].as<int>();
    p90_rate = file["p90_rate"].as<int>();
    p90_capacity = file["p90_capacity"].as<int>();
    p90_injure = file["p90_injure"].as<int>();

    // SCOUT:
    scout_damage = file["scout_damage"].as<int>();
    scout_health = file["scout_health"].as<int>();
    scout_velocity = file["scout_velocity"].as<int>();
    scout_rate = file["scout_rate"].as<int>();
    scout_capacity = file["scout_capacity"].as<int>();
    scout_injure = file["scout_injure"].as<int>();

    // Special abilties
    grenade_damage = file["grenade_damage"].as<int>();
    grenade_recharge = file["grenade_recharge"].as<int>();
    smoke_damage = file["smoke_damage"].as<int>();
    smoke_recharge = file["smoke_recharge"].as<int>();
    blitz_damage = file["blitz_damage"].as<int>();
    blitz_recharge = file["blitz_recharge"].as<int>();

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
}

Configuration::~Configuration() {
}
