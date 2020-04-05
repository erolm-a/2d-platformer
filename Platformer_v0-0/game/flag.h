#ifndef FLAG_H
#define FLAG_H

// flag: la bandiera checkpoint

#include "game_actor_generic.h"
#include "gfx/spr_vec.h"
#include "game/player.h"

class flag : public game_actor_generic
{
    bool done {false};
public:
    void spawn(int x, int y) override
    {
        own_sprite = spr_vec::new_add_sprite("res/flag.png", 2);
        own_sprite->x = x, own_sprite->y = y;
        own_sprite->set_frame(0);
    }
    void handle_collision(game_actor_generic& other) override
    {
        if(!done && typeid(other) == typeid(player)) {
            dynamic_cast<player&>(other).checkpoint = {.x = own_sprite->x,
                                                       .y =own_sprite->y};
            own_sprite->set_frame(1);
            done = true;
        }
    }


};

#endif // FLAG_H
