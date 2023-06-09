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
        bool isAlignedRight(std::shared_ptr<Collidable>& other);
        bool isAlignedLeft(std::shared_ptr<Collidable>& other);

    private:
        bool collidesWith(std::shared_ptr<Collidable>& other);
        bool isOnRight(std::shared_ptr<Collidable>& other);
        bool overlapVerticalAxis(std::shared_ptr<Collidable>& other);
        bool ovelapHorizontalAxis(std::shared_ptr<Collidable>& other);
};


#endif //LEFT4DEAD_COLLIDABLE_H
