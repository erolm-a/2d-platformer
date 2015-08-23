#include "oval_classic.h"
#include "game/wall/wall.h"
#include "game/player.h"
#include "gfx/sprite.h"
#include "init/level/room.h"
#include "audio/sample.h"

constexpr int speed = 1;
constexpr float grav_accel = 0.05f;
constexpr float grav_limit = 5.0f;

void oval_classic::spawn(int x, int y)
{
    own_sprite = new sprite("res/enemy_classic.png", 3);
    own_sprite->x = x, own_sprite->y = y;
    own_sprite->set_frame(0);
    hspeed = -speed;
    gravity_limit = grav_limit;
}

void oval_classic::handle_collision(game_instance_generic &other)
{
    // se si scontra con un muro o con una classe figlia, semplicemente torna indietro.
    if(collision_with<wall>(other))
    {
        own_sprite->x -= hspeed;
        hspeed = -hspeed;

        if(!own_sprite->is_flipped())
            own_sprite->flip_horizontal();
        else
            own_sprite->no_flip();
    }

    // se si scontra con il giocatore
    if(typeid(other) == typeid(player))
    {
        // se mi ha colpito in basso muore lui
        if(other.vspeed <= 0)

            dynamic_cast<player&>(other).is_death = true;
        else
        {
            other.vspeed = -other.vspeed;
            dynamic_cast<player&>(other).jump_fx.play();
            current_room->delete_instance(this);
        }
    }
}

void oval_classic::update()
{
    // se sotto non c'è niente
    if(!on_floor()) {
        gravity = grav_accel;
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
