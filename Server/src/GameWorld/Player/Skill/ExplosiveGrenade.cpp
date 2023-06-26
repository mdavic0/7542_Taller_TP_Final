#include "ExplosiveGrenade.h"
#include "Defines.h"


ExplosiveGrenade::ExplosiveGrenade(std::pair<int16_t, int16_t> position) :
    Grenade(TypeGrenade::grenade_explosive,  CF::grenade_damage, position) {}

void ExplosiveGrenade::applyStep(std::map<uint8_t, std::shared_ptr<Player>> &players,
                                 std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                                 double stepTime) {
    if (not available) {
        this->move(stepTime);
        this->explode(players, infecteds, stepTime);
        this->reloadingClock += stepTime;
        if (reloadingClock >= CF::grenade_recharge) {
            this->reloadingClock = 0;
            available = true;
        }
    }
}


void ExplosiveGrenade::throwGrenade(std::pair<int16_t, int16_t>& position,
                                    double elapsedTime, bool right) {
    if (this->available) {
        if (right) {
            this->position = {position.first + GRENADE_DAMAGE_RANGE, position.second};
        } else {
            this->position = {position.first - GRENADE_DAMAGE_RANGE, position.second};
        }
        this->elapsedTime = elapsedTime;
        this->setMovementDirection(right);
        this->calculateFinalPosition(right, elapsedTime);
        this->movementClock = 0;
        this->reloadingClock = 0;
        this->available = false;
    }
}
#include <iostream>
void ExplosiveGrenade::explode(std::map<uint8_t, std::shared_ptr<Player>> &players,
                               std::map<uint8_t, std::shared_ptr<Infected>> &infecteds,
                               double stepTime) {
    if (this->readyToExplode) {
        explosionClock += stepTime;
        if (explosionClock >= CF::grenade_explosion_time) {
            for (auto &player : players) {
                std::cout << "Player Pos: x:" + std::to_string(player.second->getPosition().first) + " y: " +
                             std::to_string(player.second->getPosition().second) << std::endl;
                std::cout << "Grenade Pos: x:" + std::to_string(position.first) + " y: " +
                             std::to_string(position.second) << std::endl;
                std::cout << "Distance: " + std::to_string(collidable->distance(player.second->getPosition())) + "\n\n";

                if (player.second->getCollidable()->
                    isCloseTo(this->collidable, GRENADE_DAMAGE_RANGE)) {
                    std::cout << "Estoy cerca, me pega la bombita" << std::endl;
                    player.second->applyDamage(this->damage);
                }
            }

            for (auto &infected : infecteds) {
                std::cout << "Infected Pos: x:" + std::to_string(infected.second->getPosition().first) + " y: " +
                        std::to_string(infected.second->getPosition().second) << std::endl;
                std::cout << "Grenade Pos: x:" + std::to_string(position.first) + " y: " +
                             std::to_string(position.second) << std::endl;
                std::cout << "Distance: " + std::to_string(collidable->distance(infected.second->getPosition())) + "\n\n";
                if (this->collidable->
                    isCloseTo(infected.second->getCollidable(), GRENADE_DAMAGE_RANGE)) {
                    std::cout << "Estoy cerca, me pega la bombita" << std::endl;
                    infected.second->applyDamage(this->damage);
                }
            }
            this->hasExploded = true;
            this->readyToExplode = false;
            this->explosionClock = 0;
        }
    }
}

ExplosiveGrenade::~ExplosiveGrenade() = default;
