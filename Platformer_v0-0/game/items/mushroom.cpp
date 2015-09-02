#include "mushroom.h"
#include "init/level/room.h"

constexpr int up_speed = -1;
constexpr float speed = 1;
constexpr float grav_accel = 0.05f;
constexpr float grav_limit = 5.0f;

void mushroom::update()
{
    // all'inizio sarò in un cubo, quindi mi dovrò risollevare
    if(at_first && is_sunk()) {
        vspeed = up_speed;
        return;
    }
    // se at_first è ancora attivo lo tolgo e reimposto la velocità
    if(at_first) {
        at_first = false;
        vspeed = 0;
        hspeed = speed;
    }

    // se sotto non c'è niente
    if(!on_floor()) {
        gravity = grav_accel;
        gravity_limit = grav_limit;
    }
    else
    {
        // se siamo sprofondati
        while(is_sunk())
            own_sprite->y--;
        gravity = 0;
        vspeed = 0;
    }
    // mi elimino se sono caduto
    if(own_sprite->y > current_room->win_height())
        current_room->delete_instance(this);
}
