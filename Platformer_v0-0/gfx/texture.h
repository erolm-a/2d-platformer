#ifndef TEXTURE_H
#define TEXTURE_H

// texture.cpp: wrapper

#include <SDL.h>
#include <string>
#include "font.h"

enum class blend_mode: int {
    none = SDL_BLENDMODE_NONE,
    alpha = SDL_BLENDMODE_BLEND,
    additive = SDL_BLENDMODE_ADD,
    modular = SDL_BLENDMODE_MOD
};

enum class flipping: int {
    none = SDL_FLIP_NONE,
    horizontal = SDL_FLIP_HORIZONTAL,
    vertical = SDL_FLIP_VERTICAL
};

flipping operator |(flipping& a, flipping& b);

class Texture
{
    SDL_Texture* text {nullptr};
    int img_width {0}, img_height {0};
    int access; // texture statica o in streaming
    Uint32 format; // formato del colore
    void set_info() {SDL_QueryTexture(text, &format, &access, &img_width, &img_height);}
    bool vol_type {false};

public:
    // ogni costruttore fornisce una garanzia di base.
    // N.B.: L'ultimo costruttore richiede una plain texture, ovvero una texture non creata da una
    // funzione come IMG_LoadX o TTF_RenderX. Ciò è dovuto all'impossibilità di copiare le texture
    // di default perché l'accesso è SDL_TEXTUREACCESS_STATIC.

    Texture() {}
    // carica un'immagine
    Texture(SDL_Renderer* ren, std::string path);
    // carica un testo.
    // Per le istruzioni si veda load_text
    Texture(SDL_Renderer* ren, Font& font, std::string text_to_render, SDL_Color text_colour, bool vol = false);
    // carica una texture vuota (una plain texture)
    Texture(SDL_Renderer* ren, unsigned int w, unsigned int h, SDL_TextureAccess = SDL_TEXTUREACCESS_STREAMING);
    // costruisci una texture da un'altra; possibile solo se l'altra texture è una plain_texture,
    // altrimenti lancia l'eccezione construction_failed
    Texture(Texture&);
    Texture(Texture &&) = default;
    Texture& operator =(Texture &&) = default;

    ~Texture() {free();}

    // eccezioni
    struct construction_failed{std::string what;};

    struct not_well_constructed {};

    // funzioni che non modificano la texture a basso livello

    // restituisce le dimensioni in contemporanea
    void size(unsigned &img_w, unsigned &img_h)
        {img_w = img_width, img_h = img_height;}
    // restituisce le dimensioni singole
    int width() const{return img_width;}
    int height() const{return img_height;}


    // funzioni di basso livello

    // riempie la texture con un colore. Se la texture non è stata costruita con il
    // costruttore appropriato lancia l'eccezione "not_well_constructed"
    void fill_colour(SDL_Colour colour);

    void free();

    // carica un'immagine
    void load_image(SDL_Renderer* ren, std::string path);

    // Carica un testo.
    // Dato che i testi variano spesso si deve decidere se renderli volatili o meno.
    // Se la texture è volatile, vuol dire che è creata al volo al costruttore e distrutta dal distruttore.
    // Altrimenti sarà una texture creata o al volo o da prima e sarà distrutta solo alla fine del livello.
    void load_text(SDL_Renderer* ren, Font& font,
                   std::string text_to_render, SDL_Color text_colour, bool vol = false);

    // imposta l'algoritmo di blending
    void set_blend(blend_mode bm = blend_mode::none)
        {SDL_SetTextureBlendMode(text, static_cast<SDL_BlendMode>(bm));}

    // imposta il target della texture ;
    // l'accesso deve essere SDL_TEXTUREACCESS_TARGET oppure verrà lanciata l'eccezione
    // "not_well_constructed"

    void set_target(SDL_Renderer* ren);

    void draw(SDL_Renderer* ren, SDL_Rect *orig = nullptr, SDL_Rect *dest = nullptr,
              SDL_Point* center = nullptr)
    {
        if(SDL_RenderCopyEx(ren, text, orig, dest, degree, center,
                         static_cast<SDL_RendererFlip>(static_cast<int>(flip_mode))))
        {
            SDL_Log("Orig: %d, %d, %d, %d\n", orig->x, orig->y, orig->w, orig->h);
            SDL_Log(SDL_GetError());
            throw not_well_constructed{};
        }
    }

    static void _clear();

    double degree {0.0};
    flipping flip_mode {flipping::none};


};

#endif // TEXTURE_H
