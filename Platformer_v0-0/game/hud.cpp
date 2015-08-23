#include <iostream>
#include <sstream>
#include "hud.h"
#include "game_instance_generic.h"
#include "player.h"
#include "init/level/room.h"
#include "gfx/texture.h"
#include "gfx/sprite.h"
#include "gfx/gfx_class.h"


// il gioco originale prevedeva soltanto due vite che vanno a ritroso
constexpr auto lifes = 2;

// costanti per hud::show_lives
constexpr auto death_jump = 3;
constexpr auto delay = 1000;
constexpr auto title_ptsize = 20;
constexpr auto lives_ptsize = 20;
constexpr auto back_by_n_rows = 3;
constexpr auto back_by_n_cols = 2;

player* pl {nullptr};
int life_counter {lifes};
bool managing_death {false};
void hud::set_player(player * a_player)
{
    pl = a_player;
    managing_death = false;
}

void hud::show_lives() {
    // crea una texture con sfondo nero e con il numero di vite

    // dapprima con lo sfondo
    room*& this_room = game_instance_generic::current_room;

    Texture target_txt(gfx::_get_render(), game_instance_generic::current_room->win_width(),
                                            game_instance_generic::current_room->win_height(),
                                            SDL_TEXTUREACCESS_TARGET);

    target_txt.set_target(gfx::_get_render());
    target_txt.set_blend(blend_mode::alpha);

    SDL_Colour old_colour = gfx::get_old_colour();
    SDL_SetRenderDrawColor(gfx::_get_render(), 0x00, 0x00, 0x00, 0xFF);
    gfx::clear_screen();

    // ora creiamo una texture col titolo del livello
    static TTF_Font* level_string_f = TTF_OpenFont("res/font/FifteenNarrow.ttf", title_ptsize);
    static TTF_Font* num_lives_f = TTF_OpenFont("res/font/RiseStarHandSemiBold.otf", lives_ptsize);

    SDL_Colour white{0xFF, 0xFF, 0xFF, 0xFF};

    Texture level_name(gfx::_get_render(), level_string_f, this_room->title, white);

    std::stringstream lifes_text;
    lifes_text << "x: " << life_counter;
    Texture lifes_txt(gfx::_get_render(), num_lives_f, lifes_text.str(), white, true);

    // il titolo del livello è centrato orizzontalmente
    SDL_Rect crop_levelname{
        this_room->win_width() / 2 - level_name.width() / 2,
        this_room->win_height() / 2 - level_name.height() * back_by_n_rows,
        level_name.width(), level_name.height()};

    // crea la texture di cat mario con le coordinate adeguate etc.
    sprite player_spr("res/player.png", 2, 2);
    player_spr.x = this_room->win_width() / 2 - player_spr.width() * back_by_n_cols;
    player_spr.y = this_room->win_height() / 2;

    // centra la texture delle vite
    SDL_Rect crop_lifes {
        this_room->win_width() / 2,
        this_room->win_height() / 2,
        lifes_txt.width(), lifes_txt.height()};

    level_name.draw(gfx::_get_render(), nullptr, &crop_levelname);
    SDL_Rect player_coords = {0, 0, this_room->win_width(), this_room->win_height()};
    player_spr._draw_sprite(player_coords);
    lifes_txt.draw(gfx::_get_render(), nullptr, &crop_lifes);

    SDL_SetRenderTarget(gfx::_get_render(), nullptr);
    target_txt.draw(gfx::_get_render());

    SDL_RenderPresent(gfx::_get_render());

    gfx::set_old_colour(old_colour);
    SDL_Delay(delay);
}

void hud::check_status()
{
    // se il giocatore non è morto o la musica è ferma
    if(!(pl->is_death || pl->current_room->bgm.is_playing()))
        game_instance_generic::current_room->bgm.play();

    // controlla i casi in cui si muore
    if(pl->own_sprite->y >
            game_instance_generic::current_room->win_height())
    {
        // se è gia morto fa il reset della mappa, altrimenti imposta il flag e basta
        if(!pl->is_death)
            pl->is_death = true;
        // a questo punto inizia l'animazione della morte, ovvero il giocatore salta e finisce fuori dal livello.
        // In tal caso, assicurarsi di riavviare il livello solo dopo che il giocatore cada per l'ennesima volta.
        else if(pl->vspeed >= 0)
            game_instance_generic::current_room->restart();
    }

    if(pl->is_death && !managing_death) {
        pl->current_room->bgm.halt();
        pl->set_death();
        life_counter--;
        game_instance_generic::current_room->sleep(400);
        managing_death = true;
    }
}
