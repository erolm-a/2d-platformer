#ifndef SAMPLE_H
#define SAMPLE_H

/*
 * Classe Sample: wrapper per gestire Mix_Chunk.
 * */

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <vector>

constexpr int max_volume = MIX_MAX_VOLUME;

class Sample
{
    Mix_Chunk* chunk;

    // gestire i canali è fondamentale.
    //static std::vector<bool> channel_used;
    //size_t this_channel;

    // ottimizza il caricamento dei chunk caricandoli una sola volta
    static std::unordered_map<std::string, Mix_Chunk*> used_chunks;
public:
    // costruttore di default, dove path è il nome del file audio da caricare.
    // N.B.:
    //      1) Solo il nome del file audio va specificato, non la sua strada assoluta
    //      2) Sono accettati solo file .ogg, .wav
    Sample() = default;
    Sample(std::string path);
    Sample(Sample&) = default;
    // ~Sample();

    // pulisce tutti i chunk caricati
    static void _clear();


    // funzioni di riproduzione

    // loops = 0 -> riproduci solo una volta
    // loops = n -> riproduci n+1 volte
    // loops = -1 -> riproduci infinite volte (perché mai con dei samples?)
    void play(int loops = 0);
    void pause();
    void halt();


    int set_volume(int volume = max_volume / 2);
};

#endif // SAMPLE_H
