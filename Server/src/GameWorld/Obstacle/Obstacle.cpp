#include "Obstacle.h"

Obstacle::Obstacle(TypeObstacle typeObstacle, uint8_t id, std::pair<int16_t, int16_t> &position,
                   std::shared_ptr<Collidable> collidable) {

}

void Obstacle::updatePosition(std::pair<int16_t, int16_t> &newPosition,
                              std::map<int, std::shared_ptr<Collidable>> &collidables) {
    this->move(newPosition, collidables);
}

void Obstacle::move(std::pair<int16_t, int16_t> &newPosition,
                    std::map<int, std::shared_ptr<Collidable>> &collidables) {
    auto oldPosition = this->position;
    this->position = newPosition;
    this->collidable->updatePosition(newPosition);

    if (this->collidable->collidesWith(collidables)) {
        this->position = oldPosition;
        this->collidable->updatePosition(oldPosition);
    }
}
