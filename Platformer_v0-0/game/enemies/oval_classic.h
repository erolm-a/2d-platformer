#ifndef OVAL_CLASSIC_H
#define OVAL_CLASSIC_H

// nemico di base. Esistono varie classi figlie, come "supersayan" e "turtle"
#include "game/game_instance_generic.h"

class oval_classic : public game_instance_generic
{
public:
    virtual void spawn(int x, int y) override;
    virtual void handle_collision(game_instance_generic& other) override;
    void update() override;
};

#endif // OVAL_CLASSIC_H
