#ifndef TILE_H
#define TILE_H

/*
 * tile.h: classe che gestisce il tile.
 * Serve a gestire il "modello" tile, ovvero una matrice di tile.
 * */

#include <SDL.h>
#include <string>
#include <vector>
#include "texture.h"

struct Tile;

struct tile_model
{
    friend class Tile;
    tile_model(std::string path, int tile_width, int tile_height);
    ~tile_model() = default;

    int width() const {return tile_w;} // larghezza di un tile
    int height() const {return tile_h;} // altezza di un tile
private:
    Texture texture;
    unsigned int tile_w, tile_h; // larghezza e altezza di un tile
    unsigned int img_w, img_h; // larghezza e altezza dell'immagine completa
};

struct Tile
{
    // Il parametro gid è usato da level_loader.
    // Brevemente, gid rappresenta una coordinata lineare, a partire da 0,
    // del tile da caricare dal tileset. Si veda la documentazione di Tiled
    // per i dettagli
    Tile(int gid, tile_model& tm, int x, int y);

    void draw_tile(SDL_Rect &camera);

    int x, y;
    tile_model &tileset;
private:
	SDL_Rect select;
};
#endif // TILE_H
