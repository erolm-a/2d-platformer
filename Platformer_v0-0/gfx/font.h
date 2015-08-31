#ifndef FONT_H
#define FONT_H

// Font: wrapper per TTF_Font

#include <SDL_ttf.h>
#include <SDL_video.h>
#include <string>

class Font
{
    TTF_Font* _font;
public:
    Font() = default;
    ~Font();
    Font(std::string path, int ptsize);

    // ottiene una texture con testo e colore
    SDL_Texture* _get_text(SDL_Renderer* ren, std::string text, SDL_Color colour);
};

#endif // FONT_H
