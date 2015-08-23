#include <SDL_image.h>
#include <SDL_ttf.h>
#include <cstdio>           // per memcpy
#include <iostream>
#include <string>
#include <unordered_map>
#include "texture.h"
#include "gfx_class.h"

flipping operator |(flipping& a, flipping& b)
{
   return static_cast<flipping>
           (static_cast<int>(a) | static_cast<int>(b));
}


// mappa per le texture ordinali (immagini e scritte).
// Nessun valore della mappa può essere cancellato tranne che a causa di un reset del livello.
// La chiave è una stringa contenente il file immagine da caricare o il testo.
std::unordered_map<std::string, SDL_Texture*> classic_textures;

void Texture::free()
{
    // le texture statiche possono essere distrutte solo con _clear()
    if(text && access != SDL_TEXTUREACCESS_STATIC && vol_type)
        SDL_DestroyTexture(text);
}

Texture::Texture(SDL_Renderer *ren, TTF_Font *font, std::string text_to_render, SDL_Color text_colour, bool vol)
    try {load_text(ren, font, text_to_render, text_colour, vol);}
    catch(Texture::construction_failed) { free(); throw;}

Texture::Texture(SDL_Renderer *ren, std::string path)
    try {load_image(ren, path);}
    catch(Texture::construction_failed) {free(); throw;}

void Texture::load_text(SDL_Renderer* ren, TTF_Font *font, std::string text_to_render,
                        SDL_Color text_colour, bool vol)
{
    free();

    auto p = classic_textures.find(text_to_render);
    // se la texture non è volatile e c'è già una texture adatta
    if(!vol && p != classic_textures.end())
        text = p->second;
    else {

        SDL_Surface* temp = TTF_RenderText_Blended(font, text_to_render.c_str(),
                                               text_colour);
        if(temp == nullptr)
            throw construction_failed{(std::string)"Errore in Texture::load_text: " + TTF_GetError() + '\n'};

        text = SDL_CreateTextureFromSurface(ren, temp);
        classic_textures[text_to_render] = text;
        vol_type = vol;
    }
    set_info();
}

void Texture::load_image(SDL_Renderer *ren, std::string path)
{
    auto p = classic_textures.find(path);
    if(p != classic_textures.end())
        text = p->second;
    else {
        if((text = IMG_LoadTexture(ren, path.c_str())) == nullptr)
            throw construction_failed{(std::string)"Errore in Texture::load_image: " + IMG_GetError() + '\n'};
        classic_textures[path] = text;
    }
    set_info();
}

Texture::Texture(SDL_Renderer *ren, unsigned int w, unsigned int h, SDL_TextureAccess access)
{
    if((text = SDL_CreateTexture(ren, SDL_PIXELFORMAT_RGBA8888,
                                 access, w, h))
            == nullptr)
        throw construction_failed{((std::string)"Errore in Texture::Texture(SDL_Renderer*, unsigned, unsigned): "
                                            + SDL_GetError() + '\n')};

    set_info();
}

Texture::Texture(Texture& other)
{
    if(other.access != SDL_TEXTUREACCESS_STREAMING)
        throw Texture::not_well_constructed();

    // copia i membri
    memcpy(this, &other, sizeof(Texture));
    // crea la texture, sblocca e inizializza
    this->text = SDL_CreateTexture(gfx::_get_render(), other.format, other.access, other.img_width, other.img_height);

    Uint8* this_pixels, *other_pixels;
    int pitch;
    SDL_LockTexture(text, nullptr, reinterpret_cast<void**>(&this_pixels), &pitch);
    SDL_LockTexture(text, nullptr, reinterpret_cast<void**>(&other_pixels), &pitch);

    for(int y = 0; y < img_height; y++)
        memcpy(&(this_pixels[y * pitch]), &(other_pixels[y * pitch]), pitch);

    // salva le textures
    SDL_UnlockTexture(text);
    SDL_UnlockTexture(other.text);
}

void Texture::fill_colour(SDL_Color colour)
{
    if(access != SDL_TEXTUREACCESS_STREAMING)
        throw not_well_constructed();

    // otteniamo il codice per il colore, l'accesso ai pixel e il pitch
    Uint32 colour_bytes;

#if SDL_BIG_ENDIAN
    colour_bytes = (colour.r << 24) | (colour.g << 16) | (colour.b << 8) | (colour.a);
#else
    colour_bytes = (colour.a << 24) | (colour.b << 16) | (colour.g << 8) | (colour.r);
#endif

    Uint32* pixels;
    int pitch;
    SDL_LockTexture(text, nullptr, reinterpret_cast<void**>(&pixels),  &pitch);

    for(int y = 0; y < img_height; y++)
        for(int x = 0; x < img_width; x++)
            memcpy(&(pixels[y * img_width + x]), &colour_bytes, sizeof(Uint32));

    SDL_UnlockTexture(text);
}

void Texture::set_target(SDL_Renderer *ren)
{
    if(access != SDL_TEXTUREACCESS_TARGET)
        throw Texture::not_well_constructed{};
    if(SDL_SetRenderTarget(ren, text) != 0)
        throw Texture::construction_failed{((std::string)"Errore in Texture::set_target: " + SDL_GetError() +'\n')};
}

void Texture::_clear()
{
    for(auto p = classic_textures.begin(); p != classic_textures.end(); p++)
        SDL_DestroyTexture(p->second);
}
