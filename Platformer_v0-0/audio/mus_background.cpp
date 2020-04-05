#include <SDL.h>
#include <string>
#include "mus_background.h"

void make_music_path(std::string& path)
{
    path = std::string{"res/BGM/"} + path;
}

void Mus_background::load_mus(std::string path)
{
    make_music_path(path);
    if((background = Mix_LoadMUS(path.c_str())) == nullptr)
        SDL_Log("Errore in Mus_background::Mus_background: %s\n", Mix_GetError());
}

Mus_background::~Mus_background()
{
    Mix_FreeMusic(background);
}
