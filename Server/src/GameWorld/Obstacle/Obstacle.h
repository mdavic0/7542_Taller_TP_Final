#ifndef LEFT4DEAD_OBSTACLE_H
#define LEFT4DEAD_OBSTACLE_H
#include "TypeObstacle.h"
#include <map>
#include "Collidable.h"
#include <memory>

class Obstacle {
    private:
        TypeObstacle typeObstacle;
        uint16_t id;
        std::pair<int16_t, int16_t> position;
        std::shared_ptr<Collidable> collidable;
    public:
        Obstacle(const TypeObstacle& typeObstacle, const uint16_t& id,
                 const std::pair<int16_t, int16_t>& position,
                 std::shared_ptr<Collidable> collidable);
        void updatePosition(const std::pair<int16_t, int16_t>& newPosition,
                            const std::map<uint16_t, std::shared_ptr<Collidable>>& collidables);
        std::pair<int16_t, int16_t>& getPosition();
        TypeObstacle& getTypeObstacle();
        virtual ~Obstacle() = default;

    private:
        void move(const std::pair<int16_t, int16_t> &newPosition,
                  const std::map<uint16_t, std::shared_ptr<Collidable>>& collidables);
};


#endif //LEFT4DEAD_OBSTACLE_H
