#ifndef WALL_COIN_H
#define WALL_COIN_H

// wall_coin: classe del blocco moneta

#include "wall.h"
#include "audio/sample.h"

class wall_coin : public wall
{
    Sample block_coin_fx;
protected:
    bool broken {false};

public:
    virtual void spawn(int x, int y) override;
    virtual void update() override;

    struct coin_released: public game_actor_generic {
        void spawn(int x, int y) override;
        void update() override;
    };
};
#endif // WALL_COIN_H
