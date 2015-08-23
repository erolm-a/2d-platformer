#include <SDL.h>
#include <string>
#include <vector>
#include "sample.h"

//static std::vector<bool> Sample::channel_used{false};

std::unordered_map<std::string, Mix_Chunk*> Sample::used_chunks;

//constexpr int scale_factor = 10; // aumenta di tali elementi il vettore channel_used

void absolute_path(std::string& rel_path)
{
    rel_path = (std::string)"res/effects/" + rel_path;
}

Sample::Sample(std::string path)
{
    // verifichiamo che non ci sia già un Chunk
    absolute_path(path);
    auto get_chunk = used_chunks.find(path);
    if(get_chunk != used_chunks.end())
        chunk = used_chunks[path];

    else {
        // otteniamo il primo canale utilizzabile
        /*size_t i = 0;
        for(; i < channel_used.size() && channel_used[i] == true; i++)
            ;

        // se c'è un canale disponibile, usa quello che trova;
        // altrimenti, crea altri canali, e il limite del vettore diventa canale
        this_channel = i;
        if(i == channel_used.size())
            channel_used.resize(channel_used.size() + scale_factor);
        channel_used[i] = true;*/

        if((chunk = Mix_LoadWAV(path.c_str())) == nullptr)
            SDL_Log("Errore in Sample::Sample(): %s\n", Mix_GetError());
        else
            used_chunks[path] = chunk;
    }
}

// elimina tutti i file audio
void Sample::_clear()
{
    for(auto& p : used_chunks)
        Mix_FreeChunk(p.second);

    used_chunks.clear();
}

void Sample::play(int loops)
{
    Mix_PlayChannel(-1, chunk, loops);
}

void Sample::pause()
{
    //Mix_Pause()...;
}

void Sample::halt()
{
    //Mix_HaltChannel()...
}

int Sample::set_volume(int volume)
{
    return Mix_VolumeChunk(this->chunk, volume);
}
