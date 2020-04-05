#pragma once
/*
 * La classe game_instance_generic: semplice interfaccia per gestire gli elementi del
 * gioco.
 * */

#include "event/event.h"
#include "gfx/sprite.h"
#include <typeinfo>

class room;

struct game_actor_generic
{
    static room* current_room;
    Sprite* own_sprite {};
    virtual void spawn(int x, int y) = 0;
    virtual void update() {}
    virtual void handle_key() {}
    virtual void handle_state() {}

    void update_kinematic();

    // metodo per gestire le collisioni.
    // Il metodo viene invocato da instance_container
    virtual void handle_collision(game_actor_generic& other) {(void) other;}

    template<typename S_T>
    bool collision_with(game_actor_generic& other) {
        return dynamic_cast<S_T*>(&other);
    }

    // controlla se a una determinata posizione ci potrebbe essere una collisione
    // con un oggetto. Il terzo parametro indica se l'oggetto con cui si scontrerebbe
    // deve essere solido oppure no
    game_actor_generic* check_collision(int x, int y, bool must_be_solid=true);

    // poggia su un terreno?
    bool on_floor();
    // è sprofondato?
    bool is_sunk();

    // dettagli fisici
    bool solid {false};

    // cinetica
    float hspeed {}; // > 0: verso sinistra. < 0: verso destra. = 0: fermo
    float vspeed {}; // > 0: verso il basso. < 0: verso l'alto. = 0: fermo
    float gravity {}; // 0: niente gravità
    float gravity_limit {}; // 0: nessun limite

    virtual ~game_actor_generic() {}

};
