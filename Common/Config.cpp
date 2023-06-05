#include "Config.h"
#include <iostream>
#include "Exception.h"

Config::Config(const std::string& filename) :
    file(filename), filename(filename) {
    this->loadConfig();
    this->readFile();
}

void Config::readFile() {
    if (config["hability"]) {
        const YAML::Node& skills = config["hability"];
        for (const auto& hability : skills) {
            std::string name = hability.first.as<std::string>();
            const YAML::Node& data = hability.second;

            Skill stSkill;
            stSkill.damage = data["damage"].as<int>();
            stSkill.recharge = data["recharge"].as<int>();

            this->listSkill[name] = stSkill;
        }
    }

    if (config.IsSequence()) {
        for (const auto& op : config) {
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

Operator Config::getOperator(int id) {
    return this->listOperator[id];
}

void Config::loadConfig() {
    if (!this->file.is_open())
        throw Exception("%s %s", "Failed to open config file: ", filename);
    this->config = YAML::Load(file);
}

Config::~Config() {
    if (this->file.is_open())
        this->file.close();
}

