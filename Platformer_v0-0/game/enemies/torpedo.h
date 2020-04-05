#ifndef TORPEDO_H
#define TORPEDO_H

// torpedo: il classico siluro.

#include "game/game_actor_generic.h"

class torpedo : public game_actor_generic
{
    int selected_speed;
public:
    void spawn(int x, int y) override;
    void update() override;
    void handle_collision(game_actor_generic &other) override;
};

#endif // TORPEDO_H
