#include <list>
#include <iterator>
#include <algorithm>
#include "sprite.h"
#include "spr_vec.h"

std::list<sprite*> sprite_container;

std::list<sprite*>::iterator obtain_iterator(const sprite *spr);

void spr_vec::update_spr()
{
    for(auto i: sprite_container)
        i->_update_spr();
}

void spr_vec::draw(SDL_Rect &camera)
{
    for(auto i: sprite_container)
        i->_draw_sprite(camera);
}

void spr_vec::add_sprite(sprite *spr)
{
    sprite_container.insert(obtain_iterator(spr), spr);
}

void spr_vec::delete_sprite(sprite *spr)
{
    sprite_container.remove(spr);
}

void spr_vec::clear()
{
    sprite_container.clear();
}

std::list<sprite*>::iterator obtain_iterator(const sprite *spr)
{
    /*for(auto p = sprite_container.begin();
        p != sprite_container.end(); ++p) {

        if((*p)->depth < spr->depth)
            return p;
    }
    return sprite_container.end();
    */

    auto elem = std::lower_bound(sprite_container.begin(), sprite_container.end(),
                                 spr->depth, [](const sprite* p, int depth)
    {
       return depth > p->depth;
    });
    return elem;
}
