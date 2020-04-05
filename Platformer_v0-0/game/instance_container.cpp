#include <iostream>
#include <algorithm>
#include "instance_container.h"
#include "game_actor_generic.h"
#include "gfx/spr_vec.h"
#include "gfx/sprite.h"

void instance_container::update()
{
    for(auto it_i = ins_vec.begin(); it_i != ins_vec.end(); it_i++) {
        if (it_i->deleted)
            continue;
        auto actor_i = it_i->actor;
        for(auto it_j = std::next(it_i); it_j != ins_vec.end(); it_j++) {
            if(it_j->deleted)
                continue;
            auto actor_j = it_j->actor;
            if(collide(*actor_i->own_sprite, *actor_j->own_sprite)) {
                actor_i->handle_collision(*actor_j);
                actor_j->handle_collision(*actor_i);
            }
        }
        actor_i->update();
        actor_i->update_kinematic();
    }

    collect_deleted();
}

game_actor_generic *instance_container::find_collision_at(const SDL_Rect &at,
                                                          game_actor_generic *excluded,
                                                          bool solidness)
{
    for(auto& i: ins_vec)
    {
        auto* actor = i.actor;
        if(i.actor == excluded)
            continue;
        if(actor->own_sprite->collide(at))
            if(!solidness || actor->solid)
                return actor;
    }

    return nullptr;
}

void instance_container::collect_deleted() {
    for(auto it = ins_vec.begin(); it!= ins_vec.end();) {
        auto actor = it->actor;
        if(find(deletion_pool.begin(), deletion_pool.end(), actor) != deletion_pool.end()) {
            spr_vec::delete_sprite(actor->own_sprite);
            it = ins_vec.erase(it);
        }
        else it++;
    }
}

void instance_container::delete_instance(game_actor_generic *to_delete)
{
    auto found = std::find_if(ins_vec.begin(), ins_vec.end(),
                              [to_delete](const ActorWrapper& a) {return a.actor == to_delete;});
    if (found != ins_vec.end()) {
        deletion_pool.push_back(found->actor);
        found->deleted = true;
    }
}
