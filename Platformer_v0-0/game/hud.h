#ifndef HUD_H
#define HUD_H

/*
    hud: gestisce alcuni parametri come: la vita del giocatore, le sue morti, le transizioni
    della stanza
 * */

#include "game_instance_generic.h"
#include "player.h"

namespace hud {
    // mostra le vite attuali
    void show_lives();

    // abbina "hud" all'oggetto player adeguato; la funzione è invocata da player stesso
    void set_player(player*);

    // controlla lo status del giocatore e verifica se è morto
    void check_status();

    //...
}
#endif // HUD_H
