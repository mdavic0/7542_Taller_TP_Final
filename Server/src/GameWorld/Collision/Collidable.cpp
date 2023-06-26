#include "Collidable.h"
#include <iostream>
#include <cmath>

Collidable::Collidable(uint8_t id, std::pair<int16_t, int16_t>& position,
                       int width, int height) : id(id),
                       width(width) , height(height), position(position) {
    this->topLeftCorner = {(position.first - (width / 2)) , (position.second + (height / 2))};
}

bool Collidable::collidesWith(std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    for (auto& collidable : collidables) {
        if (collidable.first != this->id){
            if (this->collidesWith(collidable.second)) {
                return true;
            }
        }
    }
    return false;
}

bool Collidable::collidesWith(std::shared_ptr<Collidable>& other) {
   if (this->ovelapHorizontalAxis(other) and
       this->overlapVerticalAxis(other)) {
       return  true;
   }
   return false;
}

void Collidable::updatePosition(std::pair<int16_t, int16_t> &pos) {
    this->position = pos;
    this->topLeftCorner = {(position.first - (width / 2.0)) ,
                           (position.second + (height / 2.0))};
}

bool Collidable::isOnRight(std::shared_ptr<Collidable> &other) {
    return (topLeftCorner.first + width) <= other->topLeftCorner.first;
}

bool Collidable::isDown(std::shared_ptr<Collidable> &other) {
    return (topLeftCorner.second + height) <= other->topLeftCorner.second;
}

int Collidable::leftDistance(std::shared_ptr<Collidable>& other) {
    return topLeftCorner.first - (other->topLeftCorner.first + other->width);
}

int Collidable::rightDistance(std::shared_ptr<Collidable>& other) {
    return other->topLeftCorner.first - (topLeftCorner.first + width);
}

int Collidable::getLeftCorner() const {
    return this->topLeftCorner.first;
}

bool Collidable::overlapVerticalAxis(std::shared_ptr<Collidable> &other) {
    if (this->topLeftCorner.second <= other->topLeftCorner.second + other->height &&
        this->topLeftCorner.second + this->height >= other->topLeftCorner.second) {
        return true;
    }
    return false;
}

bool Collidable::ovelapHorizontalAxis(std::shared_ptr<Collidable> &other) {
    if (this->topLeftCorner.first <= other->topLeftCorner.first + other->width &&
        this->topLeftCorner.first + this->width >= other->topLeftCorner.first){
        return  true;
    }
    return false;
}

bool Collidable::isAlignedRight(std::shared_ptr<Collidable> &other) {
    return (this->isOnRight(other) and (this->overlapVerticalAxis(other)));
}

bool Collidable::isAlignedLeft(std::shared_ptr<Collidable> &other) {
    return (not this->isOnRight(other) and (this->overlapVerticalAxis(other)));
}
#include <iostream>
bool Collidable::isCloseTo(std::shared_ptr<Collidable> &other, float closeDistance) {
    /*std::cout << "\nCOLLIDABLE:\nInfected Pos: x:" + std::to_string(this->position.first) + " y: " +
                 std::to_string(this->position.second) << std::endl;
    std::cout << "Grenade Pos: x:" + std::to_string(other->position.first) + " y: " +
                 std::to_string(other->position.second) << std::endl;
    std::cout << "Distance: " + std::to_string(distance(other->position)) + "\n";*/
    return (this->distance(other->position) < closeDistance);
}

double Collidable::distance(std::pair<int16_t, int16_t>& otherPos) {
    return sqrt(pow(otherPos.first - position.first, 2) +
        pow(otherPos.second - position.second, 2) * 1.0);
}
