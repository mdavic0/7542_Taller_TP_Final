#include "Configuration.h"
#include <iostream>
#include "Exception.h"
#include "Defines.h"

YAML::Node CF::file = YAML::LoadFile(PATH);
int CF::idf_damage = CF::file["idf_damage"].as<int>();
int CF::idf_health = CF::file["idf_health"].as<int>();
int CF::idf_velocity = CF::file["idf_velocity"].as<int>();
int CF::idf_rate = CF::file["idf_rate"].as<int>();
int CF::idf_capacity = CF::file["idf_capacity"].as<int>();
int CF::idf_injure = CF::file["idf_injure"].as<int>();

int CF::p90_damage = CF::file["p90_damage"].as<int>();
int CF::p90_health = CF::file["p90_health"].as<int>();
int CF::p90_velocity = CF::file["p90_velocity"].as<int>();
int CF::p90_rate = CF::file["p90_rate"].as<int>();
int CF::p90_capacity = CF::file["p90_capacity"].as<int>();
int CF::p90_injure = CF::file["p90_injure"].as<int>();

int CF::scout_damage = CF::file["scout_damage"].as<int>();
int CF::scout_health = CF::file["scout_health"].as<int>();
int CF::scout_velocity = CF::file["scout_velocity"].as<int>();
int CF::scout_rate = CF::file["scout_rate"].as<int>();
int CF::scout_capacity = CF::file["scout_capacity"].as<int>();
int CF::scout_injure = CF::file["scout_injure"].as<int>();

int CF::grenade_damage = CF::file["grenade_damage"].as<int>();
int CF::grenade_recharge = CF::file["grenade_recharge"].as<int>();
int CF::smoke_damage = CF::file["smoke_damage"].as<int>();
int CF::smoke_recharge = CF::file["smoke_recharge"].as<int>();
int CF::blitz_damage = CF::file["blitz_damage"].as<int>();
int CF::blitz_recharge = CF::file["blitz_recharge"].as<int>();
       
Configuration::Configuration() {
}

void Configuration::loadConfiguration(const std::string& filename) {
    file = YAML::LoadFile(filename);

    idf_damage = file["idf_damage"].as<int>();
    idf_health = file["idf_health"].as<int>();
    idf_velocity = file["idf_velocity"].as<int>();
    idf_rate = file["idf_rate"].as<int>();
    idf_capacity = file["idf_capacity"].as<int>();
    idf_injure = file["idf_injure"].as<int>();

    p90_damage = file["p90_damage"].as<int>();
    p90_health = file["p90_health"].as<int>();
    p90_velocity = file["p90_velocity"].as<int>();
    p90_rate = file["p90_rate"].as<int>();
    p90_capacity = file["p90_capacity"].as<int>();
    p90_injure = file["p90_injure"].as<int>();

    scout_damage = file["scout_damage"].as<int>();
    scout_health = file["scout_health"].as<int>();
    scout_velocity = file["scout_velocity"].as<int>();
    scout_rate = file["scout_rate"].as<int>();
    scout_capacity = file["scout_capacity"].as<int>();
    scout_injure = file["scout_injure"].as<int>();

    grenade_damage = file["grenade_damage"].as<int>();
    grenade_recharge = file["grenade_recharge"].as<int>();
    smoke_damage = file["smoke_damage"].as<int>();
    smoke_recharge = file["smoke_recharge"].as<int>();
    blitz_damage = file["blitz_damage"].as<int>();
    blitz_recharge = file["blitz_recharge"].as<int>();
}

Configuration::~Configuration() {
}
