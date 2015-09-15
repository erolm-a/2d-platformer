
#include <iostream>
#include <cstring> // strcmp
#include <string>
#include "recognize_types.h"
#include "level_loader.h"
#include "tinyxml2.h"
#include "room.h"
#include "game/game_instance_generic.h"
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
    if(name == (std::string)#T) \
        new_obj = game_instance_generic::current_room->create_object<T>(x, y)



void recognize_types::recognize(const XMLElement *pElem, instance_container& ic, game_instance_generic** followed)
{
    // otteniamo le coordinate
    int x, y;
    pElem->QueryIntAttribute("x", &x);
    pElem->QueryIntAttribute("y", &y);

    // se l'oggetto non ha un nome è un muro
    const char* name = pElem->Attribute("name");
    if(name == nullptr)
    {
        int w, h;
        pElem->QueryIntAttribute("width", &w);
        pElem->QueryIntAttribute("height", &h);

        ic.add_collision_box(x, y, w, h);

        // se ha l'attributo solid impostato su false
        // allora è un blocco collisione per i nemici
        if(pElem->FirstChildElement() != nullptr)
            ic.last_inserted()->solid = false;

    }
    else if(strcmp(name, "player") == 0) {
        ic.add_instance<player>(x, y);
        *followed = ic.last_inserted();
    }
    // altro
    else
        recognize(name, x, y);

    pElem->QueryBoolAttribute("visible", &(ic.last_inserted()->own_sprite->visible));
    const XMLNode *prop_node = pElem->FirstChild();
    if(prop_node != nullptr) {
        for(const XMLElement* elem = prop_node->FirstChildElement();
            elem != nullptr; elem = elem->NextSiblingElement()) {
            elem->QueryBoolAttribute("solid", &(ic.last_inserted()->solid));


            // se è un oggetto block_special

            if(name != nullptr && strcmp(name, "block_special") == 0)
                if((std::string)elem->Attribute("name") == "releases")
                    dynamic_cast<block_special&>(*ic.last_inserted()).released = elem->Attribute("value");
        }
    }
}


game_instance_generic* recognize_types::recognize(std::string name, int x, int y)
{
    game_instance_generic* new_obj;

    REGISTER_SIMPLE(wall_brick);
    else
        REGISTER_SIMPLE(wall_coin);
    else
        REGISTER_SIMPLE(wall_coin);
    else
        REGISTER_SIMPLE(oval_classic);
    else
        REGISTER_SIMPLE(supersayan);
    else
        REGISTER_SIMPLE(bad_cloud);
    else
        REGISTER_SIMPLE(turtle);
    else
        REGISTER_SIMPLE(torpedo);
    else
        REGISTER_SIMPLE(block_special);
    else
        REGISTER_SIMPLE(venom_mushroom);
    else
        REGISTER_SIMPLE(spikes);
    else
        REGISTER_SIMPLE(flag);
    else
        REGISTER_SIMPLE(tube);

    return new_obj;
}
