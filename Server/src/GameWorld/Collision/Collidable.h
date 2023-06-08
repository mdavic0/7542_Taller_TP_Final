#ifndef LEFT4DEAD_COLLIDABLE_H
#define LEFT4DEAD_COLLIDABLE_H
#include <utility>
#include <map>
#include <memory>

class Collidable {
    private:
        int id;
        std::pair<int, int> topLeftCorner;
        int width;
        int height;

    public:
        Collidable(int id, std::pair<int16_t, int16_t>& position, int width, int height);
        bool collidesWith(std::map<int, std::shared_ptr<Collidable>>& collidables);
        void updatePosition(std::pair<int16_t, int16_t>& position);
    private:
        bool collidesWith(std::shared_ptr<Collidable>& other);
};


#endif //LEFT4DEAD_COLLIDABLE_H
