#include "venom_mushroom.h"
#include "../wall/wall.h"
#include "../player.h"
#include "gfx/spr_vec.h"
#include "init/level/room.h"

constexpr int frame_venom = 2;
constexpr int mushroom_row = 1;

void venom_mushroom::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/items.png", 4, 3);
    own_sprite->x = x, own_sprite->y = y;
    own_sprite->set_row(mushroom_row);
    own_sprite->set_frame(frame_venom);
}

void venom_mushroom::handle_collision(game_actor_generic &other)
{
    if(at_first) return;

    // se si scontra con un muro o con una classe figlia, semplicemente torna indietro.
    if(collision_with<wall>(other))
    {
        own_sprite->x -= hspeed;
        hspeed = -hspeed;
    }

    // se si scontra con il giocatore muoriamo entrambi (perché lo mangia)
    if(typeid(other) == typeid(player) && dynamic_cast<player&>(other).is_death == false) {
        dynamic_cast<player&>(other).is_death = true;
        current_room->delete_instance(this);
    }
}
