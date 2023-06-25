#include "ExplosiveGrenade.h"

ExplosiveGrenade::ExplosiveGrenade(std::pair<int16_t, int16_t> position) :
    Grenade(TypeGrenade::grenade_explosive,  CF::grenade_damage, position) {}

void ExplosiveGrenade::applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                                 std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                                 double stepTime) {

}

#include <iostream>
void ExplosiveGrenade::throwGrenade(std::pair<int16_t, int16_t>& position,
                                    double elapsedTime, bool right) {
    this->position = position;
    std::cout << "Throwed ExplosiveGrenade" << std::endl;
    std::cout << "Grenade Position: (x = " << std::to_string(this->position.first) + ", y = " +
                                              std::to_string(this->position.second) + ")\n";
}

ExplosiveGrenade::~ExplosiveGrenade() = default;
