#ifndef LEFT4DEAD_COLLIDABLE_H
#define LEFT4DEAD_COLLIDABLE_H
#include <utility>
#include <map>
#include <memory>

class Collidable {
    private:
        uint8_t id;
        std::pair<int, int> topLeftCorner;
        int width;
        int height;
        std::pair<int16_t, int16_t>& position;

    public:
        Collidable(uint8_t id, std::pair<int16_t, int16_t>& position, int width, int height);
        bool collidesWith(std::map<uint8_t, std::shared_ptr<Collidable>>& collidables);
        void updatePosition(std::pair<int16_t, int16_t>& position);
        bool isAlignedRight(std::shared_ptr<Collidable>& other);
        bool isAlignedLeft(std::shared_ptr<Collidable>& other);

        bool isCloseTo(std::shared_ptr<Collidable>& other, float closeDistance);
        bool isOnRight(std::shared_ptr<Collidable>& other);
        bool isDown(std::shared_ptr<Collidable>& other);

        int leftDistance(std::shared_ptr<Collidable>& other);
        int rightDistance(std::shared_ptr<Collidable>& other);

    private:
        bool collidesWith(std::shared_ptr<Collidable>& other);
        bool overlapVerticalAxis(std::shared_ptr<Collidable>& other);
        bool ovelapHorizontalAxis(std::shared_ptr<Collidable>& other);
        float distance(std::pair<int16_t, int16_t>& otherPos);

};


#endif //LEFT4DEAD_COLLIDABLE_H
