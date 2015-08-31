#include <iostream>
#include "room.h"
#include "gfx/gfx_class.h"
#include "gfx/tile.h"
#include "game/game_instance_generic.h"
#include "level_loader.h"
#include "game/hud.h"

void room::load_lev(std::string lev_name)
{
    std::cout << "Caricamento del livello " << lev_name << std::endl;
    this->lev_name = lev_name;

    camera.x = 0;
    camera.y = 0;
    camera.w = win_width();
    camera.h = win_height();

    try {
        level_loader::open_level(lev_name);
        level_loader::load_map_properties(room_cfg);
        level_loader::parse_layer(tile_layers);
        level_loader::parse_tiles(tile_layers, tiles);
        level_loader::parse_objects(ic, &followed);
    }
    catch(level_loader::opening_except)
    {
        std::cout << "Errore nell'apertura di " << "lev_name: eccezione nella sua apertura\n";
    }
    catch(level_loader::parse_except)
    {
        std::cout << "Errore di parsing\n";
    }

    gfx::MainWindow->rename_window(room_cfg.title.c_str());
    SDL_SetRenderDrawColor(gfx::_get_render(),
                           room_cfg.background.r,
                           room_cfg.background.g,
                           room_cfg.background.b,
                           0xFF);

    bgm.load_mus(room_cfg.BGM_file);
    // mostra le vite
    hud::show_lives();
}

room::room()
{
    game_instance_generic::current_room = this;
    load_lev("1_test_new");
    gfx::set_fadein();
}

room::~room()
{
    tiles.clear();
    tile_layers.clear();
    spr_vec::clear();
}

int room::win_width() const
{
    int w, h;
    gfx::MainWindow->get_size(&w, &h);
    return w;
}

int room::win_height() const
{
    int w, h;
    gfx::MainWindow->get_size(&w, &h);
    return h;
}

game_instance_generic *room::_check_coll(game_instance_generic *me, int x, int y, bool solid)
{
    SDL_Rect new_pos {x, y, me->own_sprite->width(), me->own_sprite->height()};
    return ic.check_collision(new_pos, me, solid);
}

void room::_update_keys()
{
    ic.manage_keys();
}
void room::_update_state() {

    ic.manage_state();
}
void room::_update() {
    ic.update();

    // aggiorna camera

    int &player_x = followed->own_sprite->x;
    //int &player_y = followed->own_sprite->y;

    // se il giocatore si trova all'estrema destra o all'estrema sinistra della mappa
    // non fare niente.
    if(player_x > (win_width() / 2) && player_x < (width() - (win_width() / 2)))
        camera.x = player_x - win_width() / 2;
}

void room::_render()
{
    for(auto &i: tiles)
        i->draw_tile(camera);
    spr_vec::draw(camera);
}

void room::restart()
{
    ic.free();
    spr_vec::clear();
    load_lev(lev_name);

    gfx::set_fadein();
}
