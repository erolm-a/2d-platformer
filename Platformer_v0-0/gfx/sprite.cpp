#include <SDL.h>
#include <SDL_image.h>
#include <unordered_map>
#include <iostream>
#include <cstdio>
#include <utility>
#include <iterator>

#include "sprite.h"
#include "gfx_class.h"
#include "gfx/spr_vec.h"
#include "texture.h"

Sprite::Sprite(int x, int y, int w, int h)
{
    SDL_Log("%s:Creating empty sprite %d %d %d %d", __PRETTY_FUNCTION__, x, y, w, h);
    visible = false;
    _texture = Texture();

    spr_coords.x = x;
    spr_coords.y = y;
    spr_coords.w = _spr_mask.w = w;
    spr_coords.h = _spr_mask.h = h;
}


Sprite::Sprite(std::string path, unsigned int Xframes, unsigned int Yrows)
{
    set_sprite(path, Xframes, Yrows);
}

Sprite::~Sprite()
{
    _texture.~Texture();
}

void Sprite::set_sprite(std::string path,
                        unsigned int Xframes,
                        unsigned int Yrows)

try
{
    SDL_Log("%s:Loading sprite %s", __PRETTY_FUNCTION__, path.c_str());
    _texture.load_image(gfx::_get_render(), path);

    int img_width;
    int img_height;
    _texture.size(img_width, img_height);

    if (Xframes == 0) Xframes = 1;
    if (Yrows == 0) Yrows = 1;
    internal_path = path;
    _spr_mask.w = spr_coords.w = img_width / Xframes;
    _spr_mask.h = spr_coords.h = img_height / Yrows;

    // select the first column and row
    _spr_mask.x = 0;
    _spr_mask.y = 0;
    _spr_frames = Xframes;
    _spr_rows = Yrows;

}
catch(Texture::construction_failed &e)
{
    SDL_Log("%s\n", e.what.c_str());
}

void Sprite::set_frame(unsigned short frame)
{
    if(frame >= _spr_frames) return;
    _spr_mask.x = frame * width();
}

void Sprite::set_row(unsigned short row)
{
    if(row >= _spr_rows) return;
    _spr_mask.y = row * height();
}

void Sprite::_update_sprite()
{
    static unsigned int i = 0;
    if(speed > 0) {
        i++;
        if(i == speed) {
            i = 0;
            _spr_mask.x += width();
            if(_spr_mask.x >= width() * _spr_frames)
                _spr_mask.x = 0;
        }
    }
}

void Sprite::_draw_sprite(const SDL_Rect &camera)
{
    SDL_Rect rel_coords {spr_coords.x - camera.x,
                         spr_coords.y - camera.y,
                         spr_coords.w,
                         spr_coords.h};

    // only draw what is visible and falls inside the camera
    if(visible && rel_coords.x + spr_coords.w >= 0 && rel_coords.x <= camera.w)
        _texture.draw(gfx::_get_render(), &_spr_mask, &rel_coords);
}

SDL_Rect Sprite::extract_mask() const {
    if (collision_mask.x < 0 || collision_mask.y < 0)
        return {
            x,
            y,
            width(),
            height()
        };
    else
        return {
            x + collision_mask.x,
            y + collision_mask.y,
            collision_mask.w,
            collision_mask.h
        };
}

bool collide(const SDL_Rect& a, const SDL_Rect& b) {
    return SDL_HasIntersection(&a, &b);
}

bool Sprite::collide(const SDL_Rect& b) {
    SDL_Rect A = extract_mask();
    return SDL_HasIntersection(&A, &b);
}

bool collide(const Sprite& a, const Sprite& b) {
    SDL_Rect A = a.extract_mask() , B = b.extract_mask();

    return collide(A, B);
}

