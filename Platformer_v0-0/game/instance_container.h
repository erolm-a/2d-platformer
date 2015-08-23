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


    game_instance_generic* last_inserted() const {return ins_vec.back();}

    void update();

    // controlla una possibile collisione con qualche oggetto a una determinata posizione
    game_instance_generic* check_collision(const SDL_Rect& me,
                         game_instance_generic *excluded, bool solidness);

    void manage_keys() { for(auto* i: this->ins_vec)
                            i->handle_key();}
    void manage_state() {for(auto* i: this->ins_vec)
                            i->handle_state();}


    inline void free()
    {
        ins_vec.clear();
        ins_vec.resize(0);
    }
};


#endif // INSTANCE_CONTAINER_H
