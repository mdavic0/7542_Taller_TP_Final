#ifndef LEFT4DEAD_COLLIDABLE_H
#define LEFT4DEAD_COLLIDABLE_H
#include <utility>
#include <map>
#include <memory>

class Collidable {
    private:
        uint16_t id;
        std::pair<int, int> topLeftCorner;
        int width;
        int height;
        std::pair<int16_t, int16_t> position;

    public:
        Collidable(const uint16_t& id, const std::pair<int16_t, int16_t>& position, const int& width, const int& height);
        bool collidesWith(const std::map<uint16_t, std::shared_ptr<Collidable>>& collidables) const;
        void updatePosition(const std::pair<int16_t, int16_t>& position);
        bool isAlignedRight(const std::shared_ptr<Collidable>& other) const;
        bool isAlignedLeft(const std::shared_ptr<Collidable>& other) const;

        bool isCloseTo(const std::shared_ptr<Collidable> &other, const float& closeDistance) const;
        bool isOnRight(const std::shared_ptr<Collidable>& other) const;
        bool isDown(const std::shared_ptr<Collidable>& other) const;
        double distance(const std::pair<int16_t, int16_t>& otherPos) const;

        int leftDistance(const std::shared_ptr<Collidable>& other) const;
        int rightDistance(const std::shared_ptr<Collidable>& other) const;
        int getLeftCorner() const;

    private:
        bool collidesWith(const std::shared_ptr<Collidable>& other) const;
        bool overlapVerticalAxis(const std::shared_ptr<Collidable>& other) const;
        bool ovelapHorizontalAxis(const std::shared_ptr<Collidable>& other) const;
};


#endif //LEFT4DEAD_COLLIDABLE_H
