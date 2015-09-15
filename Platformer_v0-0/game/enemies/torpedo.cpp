#include "torpedo.h"
#include "game/player.h"
#include "init/level/room.h"
#include "gfx/gfx_class.h"

constexpr int torpedo_frame = 3;
constexpr int fall_speed = 15;

void torpedo::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/enemies.png", 8);
    own_sprite->set_frame(torpedo_frame);
    own_sprite->x = x, own_sprite->y = y;
    // metti in risalto
    own_sprite->depth = -100;

    // il muso del siluro guarda in alto normalmente. Se lo spawn è in alto
    // dovrà guardare in basso
    if(y + own_sprite->height() < 0) {
        own_sprite->flip_vertical();
        selected_speed = fall_speed;
    }
    else selected_speed = -fall_speed;
}

void torpedo::update()
{
    // imposto la velocità appena il giocatore è lì
    if(current_room->followed->own_sprite->x >= own_sprite->x)
        vspeed = selected_speed;

    // se cado fuori stanza mi elimino
    if((selected_speed > 0 && own_sprite->y >= current_room->height())
            || (selected_speed < 0 && own_sprite->y + own_sprite->height() < 0))
        current_room->delete_instance(this);
}

void torpedo::handle_collision(game_instance_generic &other)
{
    if(typeid(other) == typeid(player) && dynamic_cast<player&>(other).is_death == false)
        dynamic_cast<player&>(other).is_death = true;
}
