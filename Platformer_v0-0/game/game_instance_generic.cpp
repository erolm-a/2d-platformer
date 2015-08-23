#include "game_instance_generic.h"
#include "init/level/room.h"

room* game_instance_generic::current_room {};

void game_instance_generic::_update_kinematic()
{
    vspeed += gravity;
    if(gravity_limit != 0 && vspeed > gravity_limit)
        vspeed = gravity_limit;
    own_sprite->x += hspeed;
    own_sprite->y += vspeed;
}

game_instance_generic *game_instance_generic::check_collision(int x, int y, bool solid)
{
    return current_room->_check_coll(this, x, y, solid);
}
