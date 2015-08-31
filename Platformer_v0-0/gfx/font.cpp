#include <SDL.h>
#include "font.h"

Font::Font(std::string path, int ptsize)
{
    if((_font = TTF_OpenFont(path.c_str(), ptsize)) == nullptr)
        SDL_Log("Impossibile aprire il font %s: %s\n", TTF_GetError());
}

Font::~Font()
{
    TTF_CloseFont(_font);
}

SDL_Texture* Font::_get_text(SDL_Renderer* ren,std::string text, SDL_Color colour)
{
     SDL_Surface* temp = TTF_RenderText_Blended(_font, text.c_str(), colour);
     if(temp != nullptr) {
         SDL_Texture* txt_temp = SDL_CreateTextureFromSurface(ren, temp);
         SDL_FreeSurface(temp);
         return txt_temp;
     }
     else
         return nullptr;
}
