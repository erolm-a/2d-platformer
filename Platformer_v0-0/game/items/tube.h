#ifndef TUBE_H
#define TUBE_H

// tube: oggetto che può contenere varie cose all'interno. Il suo unico
// scopo è quello di permettere al giocatore di scendere

#include "../wall/wall.h"
#include "gfx/spr_vec.h"

class tube : public wall
{
public:
    void spawn(int x, int y) {
        own_sprite = spr_vec::new_add_sprite("res/tube.png");
        own_sprite->x = x, own_sprite->y = y;
        own_sprite->depth = -40;
    }
};

#endif // TUBE_H
