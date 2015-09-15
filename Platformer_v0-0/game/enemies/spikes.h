#ifndef SPIKES_H
#define SPIKES_H

// spikes: punte (in)visibili
#include "game/game_instance_generic.h"
#include "game/player.h"
#include "gfx/spr_vec.h"

class spikes : public game_instance_generic
{
public:
    void spawn(int x, int y) override
    {
        own_sprite = spr_vec::new_add_sprite("res/spikes.png");
        own_sprite->x = x, own_sprite->y = y;
    }
    void handle_collision(game_instance_generic& other) override
    {
        // uccide il giocatore se ci cammina o è caduto
        if(typeid(other) == typeid(player) && other.vspeed >= 0 && dynamic_cast<player&>(other).is_death == false) {
            own_sprite->visible = true;
            dynamic_cast<player&>(other).is_death = true;
        }
    }
};

#endif // SPIKES_H
