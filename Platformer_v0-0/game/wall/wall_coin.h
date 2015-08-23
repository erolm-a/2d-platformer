#ifndef WALL_COIN_H
#define WALL_COIN_H

// wall_coin: classe del blocco moneta

#include "wall.h"
#include "audio/sample.h"

class wall_coin : public wall
{
    Sample block_coin_fx;
    bool broken {false};

public:
    void spawn(int x, int y) override;
    void update() override;

    struct coin_released: public game_instance_generic {
        void spawn(int x, int y) override;
        void update() override;
    private:
        Uint32 start_tick;
    };
};
#endif // WALL_COIN_H
