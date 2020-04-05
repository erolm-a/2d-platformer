#include "game_actor_generic.h"
#include "init/level/room.h"
#include "instance_container.h"
#include <cmath>

room* game_actor_generic::current_room {};

void game_actor_generic::update_kinematic()
{
    vspeed += gravity;
    if(fabsf(gravity_limit) > 1e-6f && vspeed > gravity_limit)
        vspeed = gravity_limit;
    own_sprite->x += hspeed;
    own_sprite->y += vspeed;
}

bool game_actor_generic::on_floor()
{
    return check_collision(own_sprite->x, own_sprite->y+1);
}

bool game_actor_generic::is_sunk()
{
    return check_collision(own_sprite->x, own_sprite->y);
}

game_actor_generic *game_actor_generic::check_collision(int x, int y, bool solid)
{
    return current_room->_check_coll(this, x, y, solid);
}
