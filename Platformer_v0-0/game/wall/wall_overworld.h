#ifndef WALL_OVERWORLD_H
#define WALL_OVERWORLD_H

#include "wall.h"

class wall_overworld : public wall
{
public:
    void spawn(int x, int y) override;
};

#endif // WALL_OVERWORLD_H
