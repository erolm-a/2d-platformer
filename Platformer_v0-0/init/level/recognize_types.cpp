#include "level_loader.h"
#include "tinyxml2.h"
#include "room.h"
#include "cstring" // strcmp
#include <string>
#include "game/game_instance_generic.h"
#include "game/instance_container.h"
#include "game/player.h"
#include "game/wall/wall_brick.h"
#include "game/wall/wall_coin.h"
#include "game/enemies/oval_classic.h"
#include "game/enemies/supersayan.h"

using namespace tinyxml2;


#define str2bool(boolean_string) strcmp(boolean_string, "true") == 0

// Registra un tipo T con tutte le configurazioni adeguate
#define REGISTER(T) \
    else if(strcmp(name, #T) == 0) { \
        ic.add_instance<T>(x, y); \
        pElem->QueryBoolAttribute("visible", &(ic.last_inserted()->own_sprite->visible)); \
        \
        const XMLNode *prop_node = pElem->FirstChild(); \
        if(prop_node != nullptr) { \
            for(const XMLElement* elem = prop_node->FirstChildElement(); \
                elem != nullptr; elem = elem->NextSiblingElement()) {\
                /*const char *attr_name; */ \
                    \
                elem->QueryBoolAttribute("solid", &(ic.last_inserted()->solid)); \
            } \
        } \
    }


void recognize(const XMLElement *pElem, instance_container& ic, game_instance_generic** followed)
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
    REGISTER(wall_brick)
    REGISTER(wall_coin)
    REGISTER(oval_classic)
    REGISTER(supersayan)
}
