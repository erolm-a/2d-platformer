#include <iostream>
#include "player.h"
#include "init/level/room.h"
#include "wall/wall.h"
#include "event/event.h"
#include "gfx/sprite.h"
#include "gfx/spr_vec.h"
#include "hud.h"
#include "items/tube.h"



//constexpr unsigned short frame_walk_0 = 0;
//constexpr unsigned short frame_walk_1 = 1;
constexpr unsigned short frame_jump = 0;
constexpr unsigned short frame_death = 1;
//constexpr unsigned short row_walk = 0;
constexpr unsigned short row_other = 1;

constexpr unsigned short walk_speed = 2;
constexpr unsigned short walk_frame_speed = 10;
constexpr unsigned short jump_speed = 4;
constexpr float grav_acceleration = 0.05f;

constexpr short JUMP_VOLUME = 60;
constexpr auto jump_effect = "jump.ogg";
constexpr auto death_effect = "death.ogg";
constexpr auto diving_effect = "tube.ogg";

SDL_Point player::checkpoint {-1, -1};

void player::spawn(int x, int y)
{
    own_sprite = spr_vec::new_add_sprite("res/player.png", 2, 2);
    if(checkpoint.x < 0 && checkpoint.y < 0) {
        own_sprite->x = x;
        own_sprite->y = y;
    }
    else {
        own_sprite->x = checkpoint.x;
        own_sprite->y = checkpoint.y;
    }
    own_sprite->depth = -1;

    // normally the sprite is on the floor, unless it's being spawned in air
    is_jumping = false;
    jump_fx = Sample(jump_effect);
    jump_fx.set_volume(JUMP_VOLUME);
    death_fx = Sample(death_effect);
    underground_fx = Sample(diving_effect);

    hud::set_player(this);
}

void player::update()
{
    // if died, don't update
    hud::check_status();
    if(is_death || is_diving)
        return;
    // check if I am stading on the ground
    if(!on_floor()) {
        is_jumping = true;
        gravity = grav_acceleration;
        gravity_limit = 5;
    }

    // bounce when the head hits something
    game_actor_generic* other;
    if(vspeed < 0 && (other = check_collision(own_sprite->x, own_sprite->y + vspeed))) {
        for(; !check_collision(own_sprite->x, own_sprite->y - 1); own_sprite->y--)
            ;
        vspeed = 0;
    }

    // se c'è il terreno sotto i piedi, ma stiamo atterrando
    // oppure se siamo già atterrati
    else if(vspeed >= 0 && check_collision(own_sprite->x, own_sprite->y + vspeed)) {
        // ferma lo sprite.
        set_walk();
        stop_walk();
        vspeed = 0;
        gravity = 0;
        // A questo punto ci possono essere tre situazioni:
        // 1°: siamo atterrati perfettamente (raramente accade), e va bene così.
        // 2°: siamo sprofondati
        // 3°: stiamo levitando

        // verifichiamo se siamo sprofondati, e in tal caso saliamo
            while(is_sunk())
                own_sprite->y--;

        // altrimenti aggiusta se stiamo levitando
            while(!on_floor())
                own_sprite->y++;
    }

    // altrimenti abbiamo il terreno sotto i piedi, quindi reinizializza alla situazione
    // di default.


    if(is_jumping) {
        own_sprite->set_row(row_other);
        own_sprite->set_frame(frame_jump);
        own_sprite->speed = 0; // sprite fermo quando si alza
    }

    // se infine sono caduto dal mondo
    if(own_sprite->y > current_room->win_height())
        is_death = true;
}

void player::handle_key()
{
    if(is_death)
        return;
    // if there is a tube under the player
    if (event::get_type() == event_types::KEYDOWN &&
            event::get_key() == key_codes::DOWN && !is_diving &&
                typeid(*check_collision(own_sprite->x, own_sprite->y+1)) == typeid(tube))
        {
            is_diving = true;
            own_sprite->set_row(row_other);
            own_sprite->set_frame(frame_jump);
            vspeed = 1;
            own_sprite->depth = 100;
            underground_fx.play();
        }
    // in any case, stop walking
    stop_walk();
}

void player::handle_state()
{
    if(is_death)
        return;
    auto state = keystate::get_keystate();

    if(state[key_codes::RIGHT]) {
        if(on_floor())
            set_walk();
        own_sprite->no_flip();
        if(!check_collision(own_sprite->x + walk_speed, own_sprite->y)) {
            own_sprite->speed = walk_frame_speed;
            hspeed = walk_speed;
        }
        else stop_walk();
    }
    else if(state[key_codes::LEFT]) {
        if(on_floor())
            set_walk();
        own_sprite->flip_horizontal();
        if(!check_collision(own_sprite->x - walk_speed, own_sprite->y)) {
            own_sprite->speed = walk_frame_speed;
            hspeed = -walk_speed;
        }
        else stop_walk();
    }
    if(state[key_codes::UP]) {
        if(on_floor()) {
            set_jmp();
            vspeed = -jump_speed;
            gravity = grav_acceleration;
            gravity_limit = 5;
            jump_fx.play();
        }
    }
}

void player::set_death()
{
    stop_walk();
    is_diving = false;
    own_sprite->speed = 0;
    own_sprite->depth = -1;
    own_sprite->set_row(row_other);
    own_sprite->set_frame(frame_death);
    vspeed = -jump_speed;
    gravity = grav_acceleration;
    death_fx.play();
}
