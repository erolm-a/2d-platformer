#ifndef WALL_BRICK_H
#define WALL_BRICK_H


/*
 * wall_brick: blocco di mattoni che si può distruggere con una testata;
 * TODO: implementare un metodo per cambiare sprite a seconda del tipo di livello...
 *
 * */

#include "game/game_instance_generic.h"
#include "wall.h"
#include "audio/sample.h"
#include "init/level/room.h"


class wall_brick : public wall
{
protected:
    // riproduci il suono di rottura
    Sample break_fx;
public:
    void spawn(int x, int y) override;
    void update() override;

    /*
     * particle: particella che semplicemente cade via dal blocco rotto.
     * È un game_instance_generic in quanto richiede di movimento
     * */

    class particles : public game_instance_generic
    {
        void spawn(int x, int y) override
        {
            own_sprite = new sprite("res/particle.png");
            own_sprite->x = x, own_sprite->y = y;
        }

        void update() override
        {
            if(own_sprite->y > current_room->win_height())
                current_room->delete_instance(this);
        }
    };
};



#endif // WALL_BRICK_H
