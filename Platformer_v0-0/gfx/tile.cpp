#include "tile.h"
#include "gfx_class.h"
#include <SDL.h>
#include <SDL_image.h>
#include <string>

tile_model::tile_model(std::string path, int tile_width, int tile_height)
    :texture{gfx::_get_render(), path}
{
    this->tile_w = tile_width;
    this->tile_h = tile_height;

    texture.size(img_w, img_h);
}

Tile::Tile(int gid, tile_model &tm, int x, int y)
    : tileset {tm}
{
    int row_lenght = tileset.img_w / tileset.width();

    select.x = (gid % row_lenght) * tileset.width();
    select.y = (gid / row_lenght) * tileset.height();
    select.w = tileset.width();
    select.h = tileset.height();

    this->x = x;
    this->y = y;
}

void Tile::draw_tile(SDL_Rect &camera)
{
    SDL_Rect dst { x - camera.x,
                   y - camera.y,
                   tileset.width(),
                   tileset.height()};

    try {
        if(dst.x + tileset.width() >= 0 && dst.x <= camera.w)
            tileset.texture.draw(gfx::_get_render(), &select, &dst);
    }
    catch(Texture::not_well_constructed)
    {
        SDL_Log("Errore nel disegno: %s\n", SDL_GetError());
    }
}
