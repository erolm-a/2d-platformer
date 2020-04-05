#ifndef RECOGNIZE_TYPES_H
#define RECOGNIZE_TYPES_H

// recognize_types: metodi per ottenere l'associazione nome_tipo -> tipo_costruito
#include <string>
#include "game/instance_container.h"
#include "tinyxml2.h"

namespace recognize_types {
    // riconosce un nome oggetto e lo costruisce alla posizione {x, y} e restituisce un suo collegamento
    game_actor_generic* recognize(std::string name, int x, int y);

    // riconosce un tag oggetto e gli attributi figli e costruisce adeguatamente
    void recognize(const tinyxml2::XMLElement *pElem, instance_container& ic, game_actor_generic** followed);
}
#endif // RECOGNIZE_TYPES_H
