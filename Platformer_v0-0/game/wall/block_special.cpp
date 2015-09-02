#include "block_special.h"
#include "game/player.h"
#include "init/level/recognize_types.h"

constexpr auto pop_fx_path = "blockspawn.ogg";
constexpr int gold_frame = 5;
constexpr int empty_frame = 1;

void block_special::spawn(int x, int y)
{
    wall_coin::spawn(x, y);
    unlock_fx = Sample(pop_fx_path);
}

void block_special::update()
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
        unlock_fx.play();
        recognize_types::recognize(released, own_sprite->x, own_sprite->y);
    }
}
