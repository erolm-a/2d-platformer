#ifndef OVAL_CLASSIC_H
#define OVAL_CLASSIC_H

// nemico di base. Esistono varie classi figlie, come "supersayan" e "turtle"
#include "game/game_actor_generic.h"

class oval_classic : public game_actor_generic
{
public:
    virtual void spawn(int x, int y) override;
    virtual void handle_collision(game_actor_generic& other) override;
    void update() override;
};

#endif // OVAL_CLASSIC_H
