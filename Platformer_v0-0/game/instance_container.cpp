#include <iostream>
#include <algorithm>
#include "instance_container.h"
#include "game_instance_generic.h"
#include "gfx/spr_vec.h"
#include "gfx/sprite.h"

bool check_collision (sprite& as, sprite& bs)
{
    SDL_Rect A, B;

    // occupiamoci delle maschere di collisione

    if(as.collision_mask.x < 0 || as.collision_mask.y < 0)
    {
        A.x = as.x;
        A.y = as.y;
        A.w = as.width();
        A.h = as.height();
    }

    else
    {
        A.x = as.x + as.collision_mask.x;
        A.y = as.y + as.collision_mask.y;
        A.w = as.collision_mask.w;
        A.h = as.collision_mask.h;
    }

    if(bs.collision_mask.x < 0 || bs.collision_mask.y < 0)
    {
        B.x = bs.x;
        B.y = bs.y;
        B.w = bs.width();
        B.h = bs.height();
    }
    else
    {
        B.x = bs.x + bs.collision_mask.x;
        B.y = bs.y + bs.collision_mask.y;
        B.w = bs.collision_mask.w;
        B.h = bs.collision_mask.h;
    }

    return SDL_HasIntersection(&A, &B);
}
void instance_container::update()
{    
    for(size_t i = 0; i < ins_vec.size(); ++i) {
        for(size_t j = i + 1; j < ins_vec.size(); ++j) {

            if(::check_collision(*ins_vec[i]->own_sprite, *ins_vec[j]->own_sprite)) {
                auto* old_obj = ins_vec[i];
                try {
                    ins_vec[i]->handle_collision(*ins_vec[j]);
                    ins_vec[j]->handle_collision(*ins_vec[i]);
                }
                catch(_deleted)
                {
                    // se viene eliminato un oggetto il vettore viene riallocato.
                    // ins_vec[i] punterà a qualcos altro se è stato eliminato ins_vec[i],
                    // altrimenti sarà ins_vec[j]
                    if(ins_vec[i] != old_obj) {
                        i--;
                        goto again;
                    }
                    else
                        j -= 1;
                }
            }
        }
        // ora aggiorna l'oggetto
        try {
            ins_vec[i]->update();
            ins_vec[i]->_update_kinematic();
        }
        catch(_deleted)
        {i--; goto again;}

        // non fare niente se l'oggetto è stato eliminato
        again:
            ;
    }
}

game_instance_generic *instance_container::check_collision(const SDL_Rect &at,
                                         game_instance_generic *excluded, bool solidness)
{
    sprite me(at.x, at.y, at.w, at.h);
    me.collision_mask = excluded->own_sprite->collision_mask;

    for(auto* i: ins_vec)
    {
        if(i == excluded)
            continue;
        if(::check_collision(me, *(i->own_sprite)))
            if(!solidness || i->solid) // controlla che soddisfi i criteri di solidità
                return i;
    }

    return nullptr;
}

void instance_container::delete_instance(game_instance_generic *to_delete)
{
    auto found = std::find(ins_vec.begin(), ins_vec.end(), to_delete);

    // è stato trovato
    if(found != ins_vec.end()) {
        spr_vec::delete_sprite(to_delete->own_sprite);
        delete to_delete;
        if(found + 1 != ins_vec.end())
            std::move_backward(found + 1, ins_vec.end(), ins_vec.end()-1);
        ins_vec.resize(ins_vec.size() - 1);
        throw _deleted();
    }
}
