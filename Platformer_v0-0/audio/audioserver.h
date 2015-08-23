#ifndef AUDIOSERVER_H
#define AUDIOSERVER_H

/*
 * AudioServer: server per gestire tracce e musiche.
 * Supporta il multithreading. (TODO)
 * */

#include <SDL_mixer.h>
#include <unordered_map>
#include <string>

class AudioServer
{

public:
    AudioServer();
    ~AudioServer();
};

#endif // AUDIOSERVER_H
