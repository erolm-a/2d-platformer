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

sprite* spr_vec::new_add_sprite(std::string path, int _Xframes, int _Yframes)
{
    sprite* new_elem = new sprite(path, _Xframes, _Yframes);
    sprite_container.insert(sprite_container.begin(), new_elem);
    return new_elem;
}

sprite* spr_vec::new_add_sprite(int x, int y, int w, int h)
{
    sprite* new_elem = new sprite(x, y, w, h);
    sprite_container.insert(sprite_container.begin(), new_elem);
    return new_elem;
}

void spr_vec::delete_sprite(sprite *spr)
{
    sprite_container.remove(spr);
}

void spr_vec::clear()
{
    for(auto* i: sprite_container)
        delete i;
    sprite_container.clear();
}

std::list<sprite*>::iterator obtain_iterator(const sprite *spr)
{
    auto elem = std::lower_bound(sprite_container.begin(), sprite_container.end(),
                                 spr->depth, [](const sprite* p, int depth)
    {
       return depth > p->depth;
    });
    return elem;
}
