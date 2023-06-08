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

}

Configuration::~Configuration() {
}
