#ifndef INSTANCE_CONTAINER_H
#define INSTANCE_CONTAINER_H

/*
 * instance_container: gestisce le istanze del gioco con la tecnica RAII.
 * No, nient'altro.
 * */

#include <algorithm>
#include <vector>
#include "game_instance_generic.h"
#include "wall/wall.h"
#include "event/event.h"


class instance_container
{
    std::vector<game_instance_generic*> ins_vec {};

    struct _deleted {};
public:

    // metodi di aggiunta istanze
    template <typename S_T>
    inline game_instance_generic* add_instance(int x, int y)
    {
        game_instance_generic* new_inst = new S_T();
        new_inst->spawn(x, y);
        ins_vec.push_back(new_inst);
        return new_inst;
    }

    inline void add_collision_box(int x, int y, int w, int h)
    {
        game_instance_generic* n_wall = new collision_box(x, y, w, h);
        ins_vec.push_back(n_wall);
    }

    // elimina oggetto.
    void delete_instance(game_instance_generic* to_delete);



    // metodi di utilizzo degli oggetti
    void manage_keys() { for(auto* i: this->ins_vec)
                            i->handle_key();}
    void manage_state() {for(auto* i: this->ins_vec)
                           i->handle_state();}
    // controlla una possibile collisione con qualche oggetto a una determinata posizione
    game_instance_generic* check_collision(const SDL_Rect& at,
                         game_instance_generic *excluded, bool solidness);

    game_instance_generic* last_inserted() const {return ins_vec.back();}

    inline void free()
    {
        for(auto* i: ins_vec)
            delete i;
        ins_vec.resize(0);
    }

    void update();

    ~instance_container() {free();}
};


#endif // INSTANCE_CONTAINER_H
