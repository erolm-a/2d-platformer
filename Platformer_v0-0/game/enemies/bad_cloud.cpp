#include "bad_cloud.h"
#include "game/player.h"
#include "gfx/spr_vec.h"

void bad_cloud::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/clouds.png", 3);
    own_sprite->x = x, own_sprite->y = y;
    own_sprite->set_frame(0);
}

void bad_cloud::handle_collision(game_instance_generic &other)
{
    // se la nuvola è invisibile mette il frame del fantasma, altrimenti mette quello normale
    player* p;
    if(typeid(other) == typeid(player) && (p = dynamic_cast<player*>(&other))->is_death == false) {
        if(own_sprite->visible)
            own_sprite->set_frame(1);
        else
            own_sprite->set_frame(2);
        own_sprite->visible = true;
        p->is_death = true;
    }
}
