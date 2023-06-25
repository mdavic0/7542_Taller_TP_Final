#include "BlitzAtack.h"
#include "Configuration.h"

BlitzAtack::BlitzAtack() : damage(CF::blitz_damage), available(true),
        reloadingClock(0) {}

void BlitzAtack::applyStep(std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                           double stepTime) {

}
#include <iostream>
void BlitzAtack::throwBlitz(std::pair<int16_t, int16_t>& position) {
    // TODO: IMPACT RANGE??
    std::cout << "Throwed Blitz Atack" << std::endl;
}

bool BlitzAtack::isAvailable() {
    return this->available;
}

bool BlitzAtack::ended() {
    return false;
}
