#include "supersayan.h"
#include "../wall/wall.h"
#include "game/player.h"

void supersayan::spawn(int x, int y)
{
    oval_classic::spawn(x, y);
    own_sprite->set_frame(1);
}

void supersayan::handle_collision(game_instance_generic &other)
{
    // se si scontra con un muro o con una classe figlia, semplicemente torna indietro.
    if(collision_with<wall>(other))
    {
        own_sprite->x -= hspeed;
        hspeed = -hspeed;

        if(!own_sprite->is_flipped())
            own_sprite->flip_horizontal();
        else
            own_sprite->no_flip();
    }

    // se si scontra con il giocatore egli muore
    if(typeid(other) == typeid(player))
        dynamic_cast<player&>(other).is_death = true;
}
