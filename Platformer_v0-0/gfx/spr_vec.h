#ifndef SPR_VEC_H
#define SPR_VEC_H

/*
 * spr_vec: interfaccia del container per gestire gli sprite con
 * la tecnica RAII. Essendo un'interfaccia, non è istanziabile
 * */

#include "sprite.h"

namespace spr_vec {
    void update_spr();
    void draw(SDL_Rect& camera);
    void add_sprite(sprite *spr);
    void delete_sprite(sprite* spr);
    void clear();
}
#endif // SPR_VEC_H
