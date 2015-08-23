#ifndef LEVEL_LOADER
#define LEVEL_LOADER

/*
 * Insieme di funzioni per caricare i livelli.
 * I livelli sono salvati in formato TMX dal programma Tiled.
 * N.B.: dato che le mappe sono generate automaticamente queste funzioni non
 * gestiranno gli errori nei modi usualmente richiesti in programmi di produzione
 * */

#include <string>
#include <vector>
#include <game/instance_container.h>
#include <game/game_instance_generic.h>
#include "tinyxml2.h"
#include "gfx/tile.h"
#include "room.h"

namespace level_loader {
    // eccezione per l'apertura del file
    struct opening_except {};
    struct parse_except {};

    // Apre il file. Lancia l'eccezione opening_except nel caso fallisca
    void open_level(std::string path);

    // carica alcune proprietà della mappa
    void load_map_properties(room_info&);

    // carica tutti i livelli delle tile e li immette in un vettore
    void parse_layer(std::vector<tile_model*> &tileset);

    // carica tutti i tile.
    void parse_tiles(std::vector<tile_model*>& tilesets, std::vector<Tile *> &tiles);

    // carica tutte le istanze; following_camera è un puntatore all'oggetto da seguire
    // (il giocatore)
    void parse_objects(instance_container& ic, game_instance_generic** followed);
}
#endif // LEVEL_LOADER

