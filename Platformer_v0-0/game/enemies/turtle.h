#ifndef TURTLE_H
#define TURTLE_H

// turtle: il nemico-strumento classico per ammazzare molti nemici

#include "oval_classic.h"
#include "audio/sample.h"

class turtle : public oval_classic
{
    bool is_hit {false};
    void set_flipped();
    Sample jump_fx;
public:
    void spawn(int x, int y) override;
    void handle_collision(game_actor_generic& other) override;
};

#endif // TURTLE_H
