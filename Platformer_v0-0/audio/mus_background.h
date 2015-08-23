#ifndef MUS_BACKGROUND_H
#define MUS_BACKGROUND_H

/*
 * mus_background: wrapper per la musica
 * */
#include <SDL_mixer.h>
#include <string>

class Mus_background
{
    Mix_Music* background;
public:
    // costruttori di default.
    // N.B.: solo il nome del file audio va specificato, non la sua strada assoluta
    Mus_background() = default;
    Mus_background(std::string path) {load_mus(path);}
    Mus_background(Mus_background&) = default;
    ~Mus_background();

    void load_mus(std::string path);

    void play(int loops = -1)
        {Mix_PlayMusic(background, loops);}
    void pause()
        {Mix_PauseMusic();}

    void halt()
        {Mix_HaltMusic();}

    bool is_playing()
        {return Mix_PlayingMusic();}
    bool is_pause()
        {return Mix_PausedMusic();}
};

#endif // MUS_BACKGROUND_H
