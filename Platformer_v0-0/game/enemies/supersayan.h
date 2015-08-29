#ifndef SUPERSAYAN_H
#define SUPERSAYAN_H

// supersayan: il nemico imbattibile, ovvero l'ovale con le spine

#include "oval_classic.h"

class supersayan final: public oval_classic
{
public:
    void spawn(int x, int y) override;
    void handle_collision(game_instance_generic& other) override;
};

#endif // SUPERSAYAN_H
