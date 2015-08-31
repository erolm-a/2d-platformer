#ifndef ROOM_H
#define ROOM_H

/**
 * La classe room: gestisce i livelli, la camera, le istanze e le animazioni
 */

#include <memory>
#include <vector>
#include <string>
#include <SDL.h>
#include "gfx/spr_vec.h"
#include "game/game_instance_generic.h"
#include "game/instance_container.h"
#include "gfx/tile.h"
#include "audio/audioserver.h" // Test
#include "audio/mus_background.h"


// la struttura room_info contiene alcune informazioni circa il livello come il titolo,
// il background
struct room_info {
    std::string title = "";
    std::string BGM_file = "";
    SDL_Colour background;
    SDL_Rect level_dim;
};

class room
{
    // gestore d'istanze
    instance_container ic;

    room_info room_cfg;

    // tile_layers gestisce i tilesets mentre tiles gestisce i tile veri e propri.
    //std::vector<tile_model*> tile_layers;
    std::vector<std::unique_ptr<tile_model>> tile_layers;
    std::vector<std::unique_ptr<Tile>> tiles;
    std::string lev_name;

    void load_lev(std::string  lev_name);

    unsigned frame_sleeping {0};

    // camera è il rettangolo che rappresenta tutto ciò che si vede;
    SDL_Rect camera;

public:
    room();
    ~room();

    void _update_keys();
    void _update_state();
    void _update();
    void _render();
    // impedisce l'aggiornamento per un certo numero di millisecondi
    void sleep(unsigned int delay) {SDL_Delay(delay);}

    // ricarica la mappa.
    void restart();

    game_instance_generic* _check_coll(game_instance_generic *me, int x, int y, bool solid);

    int width() const {return room_cfg.level_dim.w;}
    int height() const {return room_cfg.level_dim.h;}
    int win_width() const;
    int win_height() const;

    template<typename T>
    game_instance_generic* create_object(int x, int y)
    {
        return ic.add_instance<T>(x, y);
    }

    void delete_instance(game_instance_generic* to_delete)
    {ic.delete_instance(to_delete);}

    AudioServer audio{};
    Mus_background bgm;

    const std::string &title = room_cfg.title;

    // followed è il puntatore all'oggetto da seguire;
    game_instance_generic* followed;
};

#endif // ROOM_H
