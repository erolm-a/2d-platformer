#include <iostream>
#include <cstring> // strcmp
#include <string>
#include "recognize_types.h"
#include "level_loader.h"
#include "tinyxml2.h"
#include "room.h"
#include "game/game_actor_generic.h"
#include "game/instance_container.h"
#include "game/player.h"
#include "game/flag.h"
#include "game/wall/wall_brick.h"
#include "game/wall/wall_coin.h"
#include "game/wall/block_special.h"
#include "game/enemies/oval_classic.h"
#include "game/enemies/supersayan.h"
#include "game/enemies/bad_cloud.h"
#include "game/enemies/torpedo.h"
#include "game/enemies/turtle.h"
#include "game/enemies/spikes.h"
#include "game/items/venom_mushroom.h"
#include "game/items/tube.h"

using namespace tinyxml2;

// mezzo piuttosto grezzo di metaprogrammazione
#define REGISTER_SIMPLE(T) \
    (name == #T && \
        (new_obj = game_actor_generic::current_room->create_object<T>(x, y)))



void recognize_types::recognize(const XMLElement *pElem, instance_container& ic, game_actor_generic** followed)
{

    // otteniamo le coordinate
    int x, y;
    pElem->QueryIntAttribute("x", &x);
    pElem->QueryIntAttribute("y", &y);

    // se l'oggetto non ha un nome è un muro
    const char* name = pElem->Attribute("name");

    game_actor_generic* last_inserted {nullptr};
    if(name == nullptr)
    {
        int w, h;
        pElem->QueryIntAttribute("width", &w);
        pElem->QueryIntAttribute("height", &h);

        last_inserted = ic.add_collision_box(x, y, w, h);

        // se ha l'attributo solid impostato su false
        // allora è un blocco collisione per i nemici
        if(pElem->FirstChildElement() != nullptr)
            last_inserted->solid = false;

    }
    else if(strcmp(name, "player") == 0) {
        last_inserted = *followed = ic.add_instance<player>(x, y);
    }
    // altro
    else
        last_inserted = recognize(name, x, y);

    if (last_inserted == nullptr)
        return;

    pElem->QueryBoolAttribute("visible", &(last_inserted->own_sprite->visible));
    const XMLNode *prop_node = pElem->FirstChild();

    // parse actor properties
    if(prop_node != nullptr) {
        for(const XMLElement* elem = prop_node->FirstChildElement();
            elem != nullptr; elem = elem->NextSiblingElement()) {
            elem->QueryBoolAttribute("solid", &(last_inserted->solid));


            if(name != nullptr && strcmp(name, "block_special") == 0
                               && strcmp(elem->Attribute("name"), "releases") == 0) {
                    SDL_Log("%s", elem->Attribute("name"));
                    dynamic_cast<block_special&>(*last_inserted).released = elem->Attribute("value");
                }
        }
    }
}


game_actor_generic* recognize_types::recognize(std::string name, int x, int y)
{
    game_actor_generic* new_obj {nullptr};

    REGISTER_SIMPLE(wall_brick) ||
    REGISTER_SIMPLE(wall_coin) ||
    REGISTER_SIMPLE(wall_coin) ||
    REGISTER_SIMPLE(oval_classic) ||
    REGISTER_SIMPLE(supersayan) ||
    REGISTER_SIMPLE(bad_cloud) ||
    REGISTER_SIMPLE(turtle) ||
    REGISTER_SIMPLE(torpedo) ||
    REGISTER_SIMPLE(block_special) ||
    REGISTER_SIMPLE(venom_mushroom) ||
    REGISTER_SIMPLE(spikes) ||
    REGISTER_SIMPLE(flag) ||
    REGISTER_SIMPLE(tube);

    return new_obj;
}
