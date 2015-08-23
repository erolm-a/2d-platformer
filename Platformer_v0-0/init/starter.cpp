#include "init.h"
#include "starter.h"
#include "event/event.h"
#include "level/room.h"

#include <SDL.h>
#include <cstdlib>

starter::starter()
{
    load_media();
    current_room = new room();

    bool quit = false;
    while(!quit)
    {
        while(event::_update_ev())
        {
            if(event::get_type() == event_types::QUIT) {
                quit = true;
            }
            current_room->_update_keys();
        }
        current_room->_update_state();
        current_room->_update();

        gfx::update();
        gfx::clear_screen();
        current_room->_render();
        gfx::render_screen();
    }
}

starter::~starter()
{
    delete current_room;
}
