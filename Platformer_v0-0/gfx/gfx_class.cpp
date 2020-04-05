#include "gfx_class.h"
#include "spr_vec.h"
#include "texture.h"
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>

Window* gfx::MainWindow {nullptr};
bool is_fading {false};

// helpers

SDL_Colour gfx::get_old_colour()
{
    Uint8 r, g, b, a;

    SDL_GetRenderDrawColor(MainWindow->renderer, &r, &g, &b, &a);
    return SDL_Colour {r, g, b, a};
}

void gfx::set_old_colour(const SDL_Colour& old) {SDL_SetRenderDrawColor
            (MainWindow->renderer, old.r, old.g, old.b, old.a);}

void free_gfx()
{
    delete gfx::MainWindow;
}

void gfx::gfx_init()
try {
    Window::window_info wi{};
    MainWindow = new Window(wi);
}
catch(Window::init_except ex)
{
    SDL_Log("Errore fatale in gfx_class alla linea %d: %s",
            __LINE__, ex.err_message.c_str());
    free_gfx();
    exit(EXIT_FAILURE);
}


void gfx::update()
{
    // Aggiungere altro qui...
    if(!is_fading)
        spr_vec::update_spr();
}

void gfx::clear_screen()
{

    // Ottieni il vecchio colore
    /*SDL_Color old_color;
    SDL_GetRenderDrawColor(MainWindow->renderer, &old_color.r,
                                                 &old_color.g,
                                                 &old_color.b,
                                                 &old_color.a);

    // Da uno sfondo di nero
    SDL_SetRenderDrawColor(MainWindow->renderer, 0xFF, 0xFF, 0xFF, 0x00); */
    SDL_RenderClear(MainWindow->renderer);

    // ripristina il colore
    /*SDL_SetRenderDrawColor(MainWindow->renderer, old_color.r,
                                                 old_color.g,
                                                 old_color.b,
                                                 old_color.a);*/
}

SDL_Renderer* gfx::_get_render()
{
    return gfx::MainWindow->renderer;
}

void gfx::render_screen()
{
    // prima disegna gli sprite e tutto il resto, poi fa la transizione

    if(is_fading)
    {
        Texture fader(MainWindow->renderer, 1, 1);

        static Uint8 alpha_fading {0xFF};

        while(alpha_fading > 0x0F) {
            SDL_Colour colour;
            colour.r = colour.g = colour.b = 0x00;
            colour.a = alpha_fading;

            fader.fill_colour(colour);
            fader.set_blend(blend_mode::alpha);
            gfx::clear_screen();
            fader.draw(MainWindow->renderer);
            SDL_RenderPresent(MainWindow->renderer);
            alpha_fading -= 0x0F;
        }
        is_fading = false;
        alpha_fading = 0xFF;
    }
    else
        SDL_RenderPresent(MainWindow->renderer);
}

void gfx::gfx_quit()
{
    Texture::_clear();
    free_gfx();
}

void gfx::set_fadein()
{
    is_fading = true;
}
