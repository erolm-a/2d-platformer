#ifndef VENOM_MUSHROOM_H
#define VENOM_MUSHROOM_H

// venom_mushroom: fungo velenoso.

#include "mushroom.h"
class venom_mushroom : public mushroom
{
public:
    void spawn(int x, int y) override;
    void handle_collision(game_actor_generic& other) override;
};

#endif // VENOM_MUSHROOM_H
