#ifndef SPRITE_H
#define SPRITE_H

/*
 * La classe sprite: gestisce gli sprite e le animazioni.
 * Molti membri sono pubblici solo perché devono essere usati dall'engine.
 * */

#include <SDL_render.h>
#include <SDL_rect.h>
#include <string>
#include "texture.h"

class sprite
{
    Texture _txture;

    unsigned short _spr_frames {1}; // numero di fotogrammi
    unsigned short _spr_rows {1}; // numero di righe
    SDL_Rect _spr_mask {0, 0, 0, 0};
    SDL_Rect spr_coords {0, 0, 0, 0};
    std::string internal_path;

    // ...

public:
    // semplice costruttore per molti sprite che non hanno bisogno di immagine e possono
    // essere sostituiti da tile.
    // l'ultimo parametro è di uso privato

    sprite(int x, int y, int w, int h);

    // costruttore classico
    sprite(std::string path, unsigned short Xframes = 1,
           unsigned short Yrows = 1); // inizializzato

    ~sprite();

    void set_sprite(std::string path, unsigned short Xframes = 1,
                    unsigned short Yrows = 1);

    // attributi fisici e visivi

    // maschera di collisione: i primi due valori sono naturalmente la coordinata
    // in pixel dell'angolo in alto a sinistra relativamente ai contorni del
    // fotogramma, gli altri sono le dimensioni;
    // con i valori "-1" la maschera è disattivata e sarà come impostare la maschera
    // a tutto il frame

    SDL_Rect collision_mask {-1, -1, 0, 0};

    // depht: indica il livello dello sprite rispetto agli altri.
    // Valori più bassi indicano che lo sprite sarà in primo piano rispetto agli
    // sprite con valori più alti
    int depth {0};
    bool visible {true};

    /* Il parametro speed gestisce la velocità di aggiornamento dello sprite.
     *
     * Dato che in questo gioco vige il VSYNC perché semplifica la gestione dei tempi,
     * non si può superare la velocità 1/1, ovvero 1 fotogramma al secondo.
     * Il VSYNC molto spesso è impostato a 60, e nel caso di velocità maggiori
     * anche il gioco sarebbe un po' più veloce. Ciò è un problema che in seguito
     * sarà risolto.
     *
     * Non si usano floating point perché, nonostante la loro semplicità, sono
     * meno precisi. Inoltre molti valori sono ricorrenti.
     * Sintassi:
     *  0: ferma lo sprite
     *  n: aggiorna lo sprite ogni n fotogrammi (1 è il più veloce)
     * */
    unsigned int speed{};


    // metodi di spostamento
    int width() const {return _spr_mask.w;}
    int height() const {return _spr_mask.h;}
    int &x = spr_coords.x;
    int &y = spr_coords.y;

    // set_frame cambia il fotogramma. L'argomento è un numero che parte da
    // 0 fino a _spr_frames meno 1.
    void set_frame(unsigned short frame);
    // alias per le righe
    void set_row(unsigned short row);

    // riflessione dell'immagine
    // nota: l'operazione è pulita, non richiede modifiche alla texture
    void no_flip() {_txture.flip_mode = flipping::none;}
    void flip_vertical() {_txture.flip_mode = flipping::vertical;}
    void flip_horizontal() {_txture.flip_mode = flipping::horizontal;}
    bool is_flipped() {return _txture.flip_mode != flipping::none;}

    // uso privato
    void _update_spr();
    void _draw_sprite(const SDL_Rect &camera);
};

#endif // SPRITE_H
