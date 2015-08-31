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

sprite::sprite(int x, int y, int w, int h)
{
    visible = false;
    _txture = Texture();

    spr_coords.x = x;
    spr_coords.y = y;
    spr_coords.w = _spr_mask.w = w;
    spr_coords.h = _spr_mask.h = h;
}


sprite::sprite(std::string path, unsigned short Xframes, unsigned short Yrows)
{
    set_sprite(path, Xframes, Yrows);
}

sprite::~sprite()
{
    _txture.~Texture();
}

void sprite::set_sprite(std::string path, unsigned short Xframes,
                        unsigned short Yrows)

try
{
    _txture.load_image(gfx::_get_render(), path);

    // imposta coordinate e dimensioni
    unsigned img_width;
    unsigned img_height;
    _txture.size(img_width, img_height);

    if (Xframes == 0) Xframes = 1;
    if (Yrows == 0) Yrows = 1;
    internal_path = path;
    _spr_mask.w = spr_coords.w = img_width / Xframes;
    _spr_mask.h = spr_coords.h = img_height / Yrows;

    _spr_mask.x = 0; // seleziona il primo frame
    _spr_mask.y = 0; // seleziona la prima riga
    _spr_frames = Xframes;
    _spr_rows = Yrows;

}
catch(Texture::construction_failed &e)
{
    SDL_Log(e.what.c_str());
}

void sprite::set_frame(unsigned short frame)
{
    if(frame >= _spr_frames) return;
    _spr_mask.x = frame * width();
}

void sprite::set_row(unsigned short row)
{
    if(row >= _spr_rows) return;
    short y;
    for(y = 0; y < row * height(); y += height())
        ;
    _spr_mask.y = y;
}

void sprite::_update_spr()
{
    static unsigned int i = 0;
    if(speed > 0) {
        i++;
        if(i == speed) {
            i = 0, _spr_mask.x += width();
            if(_spr_mask.x >= width() * _spr_frames)
                _spr_mask.x = 0;
        }
    }
}

void sprite::_draw_sprite(const SDL_Rect &camera)
{
    // elaboriamo le coordinate relative
    SDL_Rect rel_coords {spr_coords.x - camera.x,
                         spr_coords.y - camera.y,
                         spr_coords.w,
                         spr_coords.h};
    // non disegnare ciò che è fuori dalla visuale del giocatore
    if(visible && rel_coords.x + spr_coords.w >= 0 && rel_coords.x <= camera.w)
        _txture.draw(gfx::_get_render(), &_spr_mask, &rel_coords);
}
