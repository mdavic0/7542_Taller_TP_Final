#include "Venom.h"

Venom::Venom(const uint8_t& id, const std::pair<int16_t, int16_t> &position,
             std::shared_ptr<Collidable> collidable) :
             Infected(TypeInfected::infected_venom ,id, CF::venom_health,
                      CF::venom_velocity, CF::venom_damage, position,
                      std::move(collidable)) {}

void Venom::specialAtack(const std::map<uint16_t, std::shared_ptr<Infected>> &infecteds) {
    if (this->specialAtackActivated) {
        this->throwVenom();
    }
}

void Venom::throwVenom() {
    // is the same Grenade logic, unfortunately it stay out
    // of reach for delivery
}

Venom::~Venom() {

}
