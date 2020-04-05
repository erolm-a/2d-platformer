#pragma once
/*
 * instance_container: gestisce le istanze del gioco con la tecnica RAII.
 * No, nient'altro.
 * */

#include <algorithm>
#include <list>
#include <vector>
#include "game_actor_generic.h"
#include "game/wall/block_special.h"
#include "event/event.h"
#include "wall/wall.h"


class instance_container
{

    struct ActorWrapper {
        game_actor_generic* actor {nullptr};
        bool deleted {false};

        ActorWrapper() = default;
        ActorWrapper(const ActorWrapper& other) = default;

        ActorWrapper(ActorWrapper&& other) {
            actor = other.actor;
            other.actor = nullptr;
        }

        ~ActorWrapper() {
            if (actor)
                delete actor;
        }
    };

    std::list<ActorWrapper> ins_vec {};
    std::vector<game_actor_generic*> deletion_pool {};

    void collect_deleted();

    struct _deleted {};
public:

    // metodi di aggiunta istanze
    template <typename S_T>
    inline game_actor_generic* add_instance(int x, int y)
    {
        game_actor_generic* new_inst = new S_T();
        new_inst->spawn(x, y);
        ins_vec.emplace_back();
        ins_vec.back().actor = new_inst;
        return new_inst;
    }

    inline auto add_collision_box(int x, int y, int w, int h)
    {
        game_actor_generic* n_wall = new collision_box(x, y, w, h);
        ins_vec.emplace_back();
        ins_vec.back().actor = n_wall;
        return n_wall;
    }

    // elimina oggetto.
    void delete_instance(game_actor_generic* to_delete);


    // metodi di utilizzo degli oggetti
    void manage_keys() { for(auto& i: this->ins_vec)
                            i.actor->handle_key();}
    void manage_state() {for(auto& i: this->ins_vec)
                            i.actor->handle_state();}

    /**
     * @brief find_first_collision finds the first actor that collides at a
     *        specific position, i.e. such that its collision mask includes a certain rectangle.
     * @param at the "dummy" collision mask to check against
     * @param excluded an actor to exclude from this search
     * @param solidness if the resulting agent must be solid
     * @return the found colliding agent, or `nullptr` otherwise
     */
    game_actor_generic* find_collision_at(const SDL_Rect& at,
                                          game_actor_generic *excluded=nullptr,
                                          bool solidness=false);

    void update();

    void clear() {
        ins_vec.clear();
    }
};
