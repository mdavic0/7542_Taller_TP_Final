#include "SmokeGrenade.h"

SmokeGrenade::SmokeGrenade(std::pair<int16_t, int16_t> position) :
        Grenade(TypeGrenade::grenade_explosive,  CF::grenade_damage, position) {}

void SmokeGrenade::applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                             std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                             double stepTime) {

}

#include <iostream>
void SmokeGrenade::throwGrenade(std::pair<int16_t, int16_t>& position,
                                double elapsedTime, bool right) {
    this->position = position;
    std::cout << "Throwed Smoke" << std::endl;
    std::cout << "Grenade Position: (x = " << std::to_string(this->position.first) + ", y = " +
        std::to_string(this->position.second) + ")\n";
}

SmokeGrenade::~SmokeGrenade() = default;
