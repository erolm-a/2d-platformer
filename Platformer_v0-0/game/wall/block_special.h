#ifndef BLOCK_SPECIAL_H
#define BLOCK_SPECIAL_H

// block_special: blocco che rilascia oggetti speciali, che siano funghi o interi nemici
#include <string>
#include "audio/sample.h"
#include "wall_coin.h"


class block_special : public wall_coin
{
    void create_properly();
public:
    void spawn(int x, int y) override;
    void update() override;
    Sample unlock_fx;
    std::string released{};
};

#endif // BLOCK_SPECIAL_H
