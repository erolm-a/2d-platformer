#ifndef MUSHROOM_H
#define MUSHROOM_H

// mushroom: interfaccia per i vari funghi
#include "game/game_instance_generic.h"

struct mushroom : public game_instance_generic
{
    // non definisce spawn
    void update() override;
    // se un fungo non interagisse con qualcosa sarebbe molto noioso
    virtual void handle_collision(game_instance_generic &other) = 0;
protected:
    bool at_first {true};
};

#endif // MUSHROOM_H
