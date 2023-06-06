#ifndef LEFT4DEAD_P90PLAYER_H
#define LEFT4DEAD_P90PLAYER_H
#include "Player.h"
#include "Event.h"
#include "P90.h"

class P90Player : public Player {
public:
    P90Player();
    void specialAtack(Event event) override;
    ~P90Player() override;
private:
    void blitz();
};


#endif //LEFT4DEAD_P90PLAYER_H
