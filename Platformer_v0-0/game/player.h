#ifndef PLAYER_H
#define PLAYER_H

#include "game_instance_generic.h"
#include "audio/sample.h"

class player : public game_instance_generic
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

public:
    void spawn(int x, int y) override;
    void update() override;
    void handle_key() override;
    void handle_state() override;


    Sample jump_fx;
    bool is_death = false;
    // set_death imposta la sequenza di azioni che fa il giocatore quando muore:
    // imposta hspeed e gravity a certi valori, cambia il fotogramma dello sprite...
    void set_death();
};

#endif // PLAYER_H
