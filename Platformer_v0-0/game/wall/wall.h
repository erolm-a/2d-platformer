#ifndef WALL_H
#define WALL_H

/**
 * La classe wall: interfaccia per le classi wall_* derivate.
 * Tuttavia non è un interfaccia in quanto può essere istanziato.
 * Il motivo è che molti muri, eccetto le trappole, funzionano similmente,
 * e quindi si attribuisce ai tile il compito di differenziarle.
 */

#include "game/game_instance_generic.h"

struct wall : public game_instance_generic
{
    //void spawn(int x, int y, int w, int h){ solid = true; own_sprite = new sprite(x, y, w, h); }
    wall() {solid = true;}
protected:
    // il primo "spawn" serve a implementare la virtuale pura;
    // il secondo per implementare il generico muro, specificando coordinate e dimensioni
    //void spawn(int x, int y) {(void) x, (void) y;solid = true;}
};

struct collision_box : public wall
{
public:
    collision_box(int x, int y, int w, int h) {own_sprite = new sprite(x, y, w, h);}

    void spawn(int x, int y) override {(void) x, (void) y;}
};

#endif // WALL_H
