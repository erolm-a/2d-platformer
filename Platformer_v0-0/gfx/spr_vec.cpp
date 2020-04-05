#include <list>
#include <iterator>
#include <algorithm>
#include "sprite.h"
#include "spr_vec.h"

static std::list<Sprite*> sprite_container;

std::list<Sprite*>::iterator obtain_iterator(const Sprite *spr);

void spr_vec::update_spr()
{
    for(auto& i: sprite_container)
        i->_update_sprite();
}

void spr_vec::draw(SDL_Rect &camera)
{
    for(auto& i: sprite_container)
        i->_draw_sprite(camera);
}

void spr_vec::add_sprite(Sprite *spr)
{
    sprite_container.insert(obtain_iterator(spr), spr);
}

Sprite* spr_vec::new_add_sprite(std::string path, int _Xframes, int _Yframes)
{
    Sprite* new_elem = new Sprite(path, _Xframes, _Yframes);
    sprite_container.push_back(new_elem);
    return new_elem;
}

Sprite* spr_vec::new_add_sprite(int x, int y, int w, int h)
{
    Sprite* new_elem;
    //new_elem = new Sprite(x, y, w, h)
    for(int i = 0; i < 40; i++)
        new_elem = new Sprite(x, y, w, h);
    // Sprite* new_elem = new Sprite(x, y, w, h);
    sprite_container.push_back(new_elem);
    return new_elem;
}

void spr_vec::delete_sprite(Sprite *spr)
{
    sprite_container.remove(spr);
    delete spr;
}

void spr_vec::clear()
{
    for(auto* i: sprite_container)
        delete i;
    sprite_container.clear();
}

std::list<Sprite*>::iterator obtain_iterator(const Sprite *spr)
{
    auto elem = std::lower_bound(sprite_container.begin(), sprite_container.end(),
                                 spr->depth, [](const Sprite* p, int depth)
    {
       return depth > p->depth;
    });
    return elem;
}
