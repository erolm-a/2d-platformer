#include <cstdlib> // atexit
#include <iostream>
#include <SDL.h>
#include "audioserver.h"
#include "sample.h"

AudioServer::AudioServer()
{

    if(Mix_Init(MIX_INIT_MID | MIX_INIT_OGG | MIX_INIT_MP3) < 0) {
        // Nonostante il suono non ci sia, il gioco rimane fruibile
        SDL_Log("Errore in AudioServer::AudioServer(): %s\n"
                "L'audio non sarà disponibile",
                Mix_GetError());

        //valid = false;
    }

    atexit(Mix_Quit);

    constexpr auto stereo = 2;
    constexpr auto chunk_size = 2048;
    if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, stereo, chunk_size)
            != 0)
    {
        SDL_Log("Errore in AudioServer::AudioServer(): %s\n", Mix_GetError());
        //valid = false;
        return;
    }
}

AudioServer::~AudioServer()
{
    Sample::_clear();
    Mix_CloseAudio();
}
