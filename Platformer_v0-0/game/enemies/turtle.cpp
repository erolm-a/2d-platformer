#include "turtle.h"
#include "game/wall/wall.h"
#include "game/player.h"
#include "init/level/room.h"
#include "gfx/gfx_class.h"

constexpr unsigned turtle_frame {1};
constexpr unsigned flipped_frame {2};

// maschere di collisione per il frame normale e quello invertito
constexpr int collision_x {1};
constexpr int collision_y {4};
constexpr int collision_w {30};
constexpr int collision_h {38};

constexpr int collision_flipped_x {1};
constexpr int collision_flipped_y {15};
constexpr int collision_flipped_w {30};
constexpr int collision_flipped_h {27};

constexpr int walk_speed {1};
constexpr int flipped_speed {5};

void turtle::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/enemies.png", 8);
    own_sprite->set_frame(turtle_frame);
    own_sprite->x = x, own_sprite->y = y;
    own_sprite->collision_mask = {collision_x, collision_y, collision_w, collision_h};

    hspeed = walk_speed;
    jump_fx = Sample("turtle.ogg");
}

void turtle::set_flipped()
{
    own_sprite->set_frame(flipped_frame);
    own_sprite->collision_mask = {collision_flipped_x, collision_flipped_y,
                                  collision_flipped_w, collision_flipped_h};
    hspeed = 0;
    is_hit = true;
}

void turtle::handle_collision(game_instance_generic &other)
{
    player* p;
    // se è un muro:
    //   se non sono stato coricato si comporta normalmente;
    //   altrimenti se sono stato coricato ma il muro non è marcatore si comporta normalmente;
    //   altrimenti lascia perdere
    if(collision_with<wall>(other) && (!is_hit || other.solid))
    {
        own_sprite->x -= hspeed;
        hspeed = -hspeed;

        if(!own_sprite->is_flipped())
            own_sprite->flip_horizontal();
        else
            own_sprite->no_flip();
    }

    // se è un giocatore
    else if(typeid(other) == typeid(player) && (p = dynamic_cast<player*>(&other))->is_death == false)
    {
        // egli muore se mi ha colpito male e non sono fermo
        if(p->vspeed <= 0 && hspeed != 0)
            p->is_death = true;

        // se non sono rovesciato lo divento
        else if(!is_hit)
                set_flipped();

        // imposta una direzione adeguata
        else if(hspeed == 0) {
            if(p->own_sprite->x < own_sprite->x + own_sprite->width() / 2)
                hspeed = flipped_speed;
            else
                hspeed = -flipped_speed;
        }
        // ferma l'oggetto
        else
            hspeed = 0;

        p->vspeed = -(p->vspeed);
        jump_fx.play();
    }

    // se è un altro nemico
    else if(is_hit && hspeed != 0 && collision_with<oval_classic>(other))
        current_room->delete_instance(&other);
}
