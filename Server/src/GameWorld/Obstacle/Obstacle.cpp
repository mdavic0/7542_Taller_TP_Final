#include "Obstacle.h"

#include <utility>

Obstacle::Obstacle(TypeObstacle typeObstacle, uint8_t id, std::pair<int16_t, int16_t> &position,
                   std::shared_ptr<Collidable> collidable) : typeObstacle(typeObstacle), id(id),
                   position(position), collidable(std::move(collidable)) {}

void Obstacle::updatePosition(std::pair<int16_t, int16_t> &newPosition,
                              std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    this->move(newPosition, collidables);
}

void Obstacle::move(std::pair<int16_t, int16_t> &newPosition,
                    std::map<uint8_t, std::shared_ptr<Collidable>> &collidables) {
    auto oldPosition = this->position;
    this->position = newPosition;
    this->collidable->updatePosition(newPosition);

    if (this->collidable->collidesWith(collidables)) {
        this->position = oldPosition;
        this->collidable->updatePosition(oldPosition);
    }
}

std::pair<int16_t, int16_t>& Obstacle::getPosition() {
    return position;
}

TypeObstacle& Obstacle::getTypeObstacle() {
    return typeObstacle;
}
