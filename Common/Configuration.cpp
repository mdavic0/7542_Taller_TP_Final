#include "Configuration.h"
#include <iostream>
#include "Exception.h"

Configuration::Configuration() {
}

void Configuration::loadConfiguration(const std::string& filename) {
    file = YAML::LoadFile(filename);
    if (file["hability"]) {
        const YAML::Node& skills = file["hability"];
        for (const auto& hability : skills) {
            std::string name = hability.first.as<std::string>();
            const YAML::Node& data = hability.second;

            Skill stSkill;
            stSkill.damage = data["damage"].as<int>();
            stSkill.recharge = data["recharge"].as<int>();

            listSkill[name] = stSkill;
        }
    }

    if (file.IsSequence()) {
        for (const auto& op : file) {
            Operator stOperator;
            stOperator.type = TypeOperator(op["name"].as<int>());
            stOperator.damage = op["damage"].as<int>();
            stOperator.health = op["health"].as<int>();
            stOperator.velocity = op["velocity"].as<int>();
            stOperator.rate = op["rate"].as<int>();
            stOperator.capacity = op["capacity"].as<int>();
            stOperator.injure = op["injure"].as<int>();

            const YAML::Node& skills = op["skills"];
            for (const auto& skill : skills) {
                std::string name = skill.as<std::string>();
                stOperator.skills[name] = listSkill[name];
            }
            listOperator[(int)stOperator.type] = stOperator;
        }
    }
}

Configuration::~Configuration() {
}
