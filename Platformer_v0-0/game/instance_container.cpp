#include <iostream>
#include <algorithm>
#include "instance_container.h"
#include "game_instance_generic.h"
#include "gfx/spr_vec.h"

bool check_collision (game_instance_generic* a, game_instance_generic* b)
{
    sprite& as = *(a->own_sprite);
    sprite& bs = *(b->own_sprite);

    SDL_Rect A = {as.x, as.y, as.width(), as.height()};
    SDL_Rect B = {bs.x, bs.y, bs.width(), bs.height()};

    return SDL_HasIntersection(&A, &B);
}
void instance_container::update()
{    
    for(int i = 0; i < ins_vec.size(); ++i) {
        for(int j = i + 1; j < ins_vec.size(); ++j) {

            if(::check_collision(ins_vec[i], ins_vec[j])) {
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

game_instance_generic *instance_container::check_collision(const SDL_Rect &me,
                                         game_instance_generic *excluded, bool solidness)
{
    for(auto* i: ins_vec)
    {
        if(i == excluded)
            continue;
        SDL_Rect other {i->own_sprite->x,
                        i->own_sprite->y,
                        i->own_sprite->width(),
                        i->own_sprite->height()};
        if(SDL_HasIntersection(&me, &other)) // se è avvenuta la collisione
            if(!solidness || (solidness && i->solid)) // se l'altro oggetto è solido
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
