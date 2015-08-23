#ifndef WALL_OVERWORLD_H
#define WALL_OVERWORLD_H

#include "wall.h"

class wall_overworld : public wall
{
public:
    void spawn(int x, int y) override;
    //void update() {;}
    void handle_collision(game_instance_generic& other) override;
};

#endif // WALL_OVERWORLD_H
