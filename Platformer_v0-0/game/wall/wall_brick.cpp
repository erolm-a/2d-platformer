#include "game/player.h"
#include "wall_brick.h"
#include "init/level/room.h"

constexpr float grav_acceleration = 0.15f;
constexpr float particle_jump = -1;
constexpr int particle_leftright = 1;

void wall_brick::spawn(int x, int y)
{
    own_sprite = new sprite("res/block.png", 6, 3);
    own_sprite->set_frame(0);

    own_sprite->x = x, own_sprite->y = y;
    break_fx = Sample("blockbreak.ogg");
}

void wall_brick::update()
{
    auto* other = check_collision(own_sprite->x + own_sprite->width() / 2, own_sprite->y + 1, false);
    if(other != nullptr && collision_with<player>(*other))
    {
        if(dynamic_cast<player*>(other)->is_death)
            return;

        other->vspeed = 0;
        break_fx.play();
        // crea le particelle sul blocco
        game_instance_generic* particles_vec[4];

        for(int i = 0; i < 4; i++) {
            particles_vec[i] = current_room->create_object<particles>(own_sprite->x + own_sprite->width() / 2,
                                own_sprite->y);
            particles_vec[i]->gravity = grav_acceleration;
        }
        particles_vec[0]->vspeed = particles_vec[2]->vspeed = particle_jump;
        particles_vec[1]->vspeed = particles_vec[3]->vspeed = 2 * particle_jump;
        particles_vec[0]->hspeed = particles_vec[1]->hspeed = -particle_leftright;
        particles_vec[2]->hspeed = particles_vec[3]->hspeed = particle_leftright;

        // mi elimino
        current_room->delete_instance(this);
    }
}
