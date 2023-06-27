#include "Collidable.h"
#include <iostream>
#include <cmath>
#include <iostream>

Collidable::Collidable(const uint16_t& id, const std::pair<int16_t, int16_t>& position,
                       const int& width, const int& height) : id(id),
                       width(width) , height(height), position(position) {
    this->topLeftCorner = {(position.first - (width / 2)) , (position.second + (height / 2))};
}

bool Collidable::collidesWith(const std::map<uint16_t, std::shared_ptr<Collidable>> &collidables) const {
    for (auto& collidable : collidables) {
        if (collidable.first != this->id){
            if (this->collidesWith(collidable.second)) {
                return true;
            }
        }
    }
    return false;
}

bool Collidable::collidesWith(const std::shared_ptr<Collidable>& other) const {
   if (this->ovelapHorizontalAxis(other) and
       this->overlapVerticalAxis(other)) {
       return  true;
   }
   return false;
}

void Collidable::updatePosition(const std::pair<int16_t, int16_t> &pos) {
    this->position = pos;
    this->topLeftCorner = {(position.first - (width / 2.0)) ,
                           (position.second + (height / 2.0))};
}

bool Collidable::isOnRight(const std::shared_ptr<Collidable> &other) const {
    return (topLeftCorner.first + width) <= other->topLeftCorner.first;
}

bool Collidable::isDown(const std::shared_ptr<Collidable> &other) const {
    return (topLeftCorner.second + height) <= other->topLeftCorner.second;
}

int Collidable::leftDistance(const std::shared_ptr<Collidable>& other) const {
    return topLeftCorner.first - (other->topLeftCorner.first + other->width);
}

int Collidable::rightDistance(const std::shared_ptr<Collidable>& other) const {
    return other->topLeftCorner.first - (topLeftCorner.first + width);
}

int Collidable::getLeftCorner() const {
    return this->topLeftCorner.first;
}

bool Collidable::overlapVerticalAxis(const std::shared_ptr<Collidable> &other) const {
    if (this->topLeftCorner.second <= other->topLeftCorner.second + other->height &&
        this->topLeftCorner.second + this->height >= other->topLeftCorner.second) {
        return true;
    }
    return false;
}

bool Collidable::ovelapHorizontalAxis(const std::shared_ptr<Collidable> &other) const {
    if (this->topLeftCorner.first <= other->topLeftCorner.first + other->width &&
        this->topLeftCorner.first + this->width >= other->topLeftCorner.first){
        return  true;
    }
    return false;
}

bool Collidable::isAlignedRight(const std::shared_ptr<Collidable> &other) const {
    return (this->isOnRight(other) and (this->overlapVerticalAxis(other)));
}

bool Collidable::isAlignedLeft(const std::shared_ptr<Collidable> &other) const {
    return (not this->isOnRight(other) and (this->overlapVerticalAxis(other)));
}

bool Collidable::isCloseTo(const std::shared_ptr<Collidable> &other, const double& closeDistance) const {
    return (this->distance(other->position) < closeDistance);
}

double Collidable::distance(const std::pair<int16_t, int16_t>& otherPos) const {
    return sqrt(pow(otherPos.first - position.first, 2) +
        pow(otherPos.second - position.second, 2) * 1.0);
}
