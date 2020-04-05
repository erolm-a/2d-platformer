#include "wall_overworld.h"
#include "gfx/spr_vec.h"
#include <iostream>

constexpr unsigned overworld_row = 0;
constexpr unsigned overworld_frame_0 = 0;
constexpr unsigned overworld_frame_1 = 3;
constexpr unsigned overworld_frame_2 = 4;
constexpr unsigned overworld_frame_normal = 2;

void wall_overworld::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/block.png", 6, 3);
    own_sprite->x = x;
    own_sprite->y = y;
    own_sprite->set_row(overworld_row);

    auto height = own_sprite->height();

    /*
     * 0 - frame_normal
     * 1 - .....
     * 2 - frame_0
     * 3 - frame_1
     * 4 - frame_2
     * 5 - ...
     * */
    if(y >= 480 - height)
        own_sprite->set_frame(overworld_frame_2);
    else if(y >= 480 - 2 * height)
        own_sprite->set_frame(overworld_frame_1);
    else if(y >= 480 - 3 * height)
        own_sprite->set_frame(overworld_frame_0);
    else
        own_sprite->set_frame(overworld_frame_normal);
}
