#ifndef PLAYER_H
#define PLAYER_H

#include "game_actor_generic.h"
#include "audio/sample.h"
#include <tuple>

class player : public game_actor_generic
{
    // aiutanti
    void set_walk() {is_jumping = false; own_sprite->set_row(0);
                     gravity = 0;}
    void set_jmp() {is_jumping = true;}
    void stop_walk() {own_sprite->set_frame(0); own_sprite->speed = 0;
                     hspeed = 0;}

    // effetti sonori

    Sample death_fx;

    bool is_jumping {false};

    // per il tubo
    bool is_diving {false};
    Sample underground_fx;

public:
    void spawn(int x, int y) override;
    void update() override;
    void handle_key() override;
    void handle_state() override;


    Sample jump_fx;
    bool is_death {false};
    // set_death imposta la sequenza di azioni che fa il giocatore quando muore:
    // imposta hspeed e gravity a certi valori, cambia il fotogramma dello sprite...
    void set_death();

    static SDL_Point checkpoint;

};

#endif // PLAYER_H
