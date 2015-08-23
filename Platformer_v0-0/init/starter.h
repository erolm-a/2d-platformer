#ifndef STARTER_H
#define STARTER_H

/**
 * @brief La starter class. Avvia tutto il necessario.
 */

#include "gfx/gfx_class.h"
#include "init/level/room.h"

class starter
{
    room *current_room {nullptr};
public:
    starter();
    ~starter();
};

#endif // STARTER_H
