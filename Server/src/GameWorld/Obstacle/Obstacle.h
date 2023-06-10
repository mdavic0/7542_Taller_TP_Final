#ifndef LEFT4DEAD_OBSTACLE_H
#define LEFT4DEAD_OBSTACLE_H
#include "TypeObstacle.h"
#include <map>
#include "Collidable.h"
#include <memory>

class Obstacle {
    private:
        TypeObstacle typeObstacle;
        uint8_t id;
        std::pair<int16_t, int16_t> position;
        std::shared_ptr<Collidable> collidable;
    public:
        Obstacle(TypeObstacle typeObstacle, uint8_t id,
                 std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);
        void updatePosition(std::pair<int16_t, int16_t>& newPosition,
                            std::map<uint8_t, std::shared_ptr<Collidable>>& collidables);
        virtual ~Obstacle() = default;

    private:
        void move(std::pair<int16_t, int16_t> &newPosition,
                  std::map<uint8_t, std::shared_ptr<Collidable>>& collidables);
};


#endif //LEFT4DEAD_OBSTACLE_H
