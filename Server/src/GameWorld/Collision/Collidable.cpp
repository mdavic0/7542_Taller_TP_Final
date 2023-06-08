#include "Collidable.h"

Collidable::Collidable(int id, std::pair<int16_t, int16_t>& position,
                       int width, int height) : id(id),
                       width(width) , height(height) {
    this->topLeftCorner = {(position.first - (width / 2)) , (position.second + (height / 2))};
}
#include <iostream>
bool Collidable::collidesWith(std::map<int, std::shared_ptr<Collidable>> &collidables) {
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
   // std::cout << "(" << this->topLeftCorner.first << "," << this->topLeftCorner.second << ")\n";
   // std::cout << "(" << other->topLeftCorner.first << "," << other->topLeftCorner.second << ")\n";
   if (this->topLeftCorner.first < other->topLeftCorner.first + other->width &&
        this->topLeftCorner.first + this->width > other->topLeftCorner.first &&
        this->topLeftCorner.second < other->topLeftCorner.second + other->height &&
        this->topLeftCorner.second + this->height > other->topLeftCorner.second) {
       // std::cout << "Hay colision!\n";
       return  true;
   }
   return false;
}

void Collidable::updatePosition(std::pair<int16_t, int16_t> &position) {
    this->topLeftCorner = {(position.first - (width / 2)) , (position.second + (height / 2))};
}
