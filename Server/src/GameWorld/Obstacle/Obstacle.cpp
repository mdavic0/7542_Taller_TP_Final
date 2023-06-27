#include "Obstacle.h"

#include <utility>

Obstacle::Obstacle(const TypeObstacle& typeObstacle, const uint16_t& id, const std::pair<int16_t, int16_t> &position,
                   std::shared_ptr<Collidable> collidable) : typeObstacle(typeObstacle), id(id),
                   position(position), collidable(std::move(collidable)) {}

void Obstacle::updatePosition(const std::pair<int16_t, int16_t> &newPosition,
                              const std::map<uint16_t, std::shared_ptr<Collidable>> &collidables) {
    this->move(newPosition, collidables);
}

void Obstacle::move(const std::pair<int16_t, int16_t> &newPosition,
                    const std::map<uint16_t, std::shared_ptr<Collidable>> &collidables) {
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
