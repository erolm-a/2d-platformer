#pragma once
/*
 * spr_vec: interfaccia del container per gestire gli sprite con
 * la tecnica RAII. Essendo un'interfaccia, non è istanziabile
 * */

#include <string>
#include "sprite.h"

namespace spr_vec {
    // aggiorna gli sprite
    void update_spr();

    // disegna gli sprite informandoli sul valore "camera"
    void draw(SDL_Rect& camera);

    // aggiunge uno sprite all'elenco
    void add_sprite(Sprite *spr);

    // inizializza uno sprite, lo aggiunge a un'elenco e ne da un puntatore
    Sprite* new_add_sprite(std::string path, int _Xframes = 1, int _Yframes = 1);
    Sprite* new_add_sprite(int x, int y, int w, int h);

    void delete_sprite(Sprite* spr);
    void clear();
}
