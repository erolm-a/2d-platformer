#include "game/game_instance_generic.h"
#include "gfx/sprite.h"
#include "game/player.h"
#include "wall_coin.h"
#include "init/level/room.h"

constexpr int gold_frame = 5;
constexpr int empty_frame = 1;

void wall_coin::spawn(int x, int y)
{
    own_sprite = new sprite("res/block.png", 6, 3);
    own_sprite->x = x, own_sprite->y = y;
    own_sprite->set_frame(gold_frame);

    block_coin_fx = Sample("blockcoin.ogg");
}

void wall_coin::update()
{
    // se wall_coin è invisibile non è nemmeno solido
    if(!own_sprite->visible)
        solid = false;

    auto* p = check_collision(own_sprite->x + own_sprite->width()/2,
                              own_sprite->y + 1, false);

    // se è stato colpito dal giocatore dal basso
    if(p != nullptr && collision_with<player>(*p)
            && p->own_sprite->y > this->own_sprite->y &&
            p->vspeed < 0 && !broken) {
        // nel caso l'oggetto fosse stato invisibile
        own_sprite->visible = true;
        solid = true;

        broken = true;
        own_sprite->set_frame(empty_frame);
        block_coin_fx.play();
        // gestisce l'animazione della moneta...
        current_room->create_object<wall_coin::coin_released>(own_sprite->x, own_sprite->y - 1);
    }
}

constexpr float grav_accel = 0.15f;
constexpr int jump = -4;
void wall_coin::coin_released::spawn(int x, int y)
{
    own_sprite = new sprite("res/items.png", 4, 3);
    own_sprite->set_frame(0);
    own_sprite->x = x, own_sprite->y = y;
    vspeed = jump;
    gravity = grav_accel;
}

void wall_coin::coin_released::update()
{
    if(vspeed >= 0)
        current_room->delete_instance(this);
}
