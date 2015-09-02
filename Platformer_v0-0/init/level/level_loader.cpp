#include <list>
#include <memory>
#include <string>
#include <cstring>
#include <cstring>
#include <vector>
#include <iostream>
#include "level_loader.h"
#include "recognize_types.h"
#include "tinyxml2.h"
#include "game/player.h"
#include "game/wall/wall_brick.h"

using namespace tinyxml2;
using namespace std;

// piccola funzione per un minimo controllo di errore
template<typename EX_T>
inline void assert_except(void* pointer) { if(pointer == nullptr) throw EX_T();}

namespace configs
{
    XMLDocument xmlDoc;
    string doc_name = "";
    XMLNode *pRoot;
    // velocizza il caricamento se deve essere veloce
    bool reload {false};

    int width;  // width ed height si riferiscono alla grandezza del livello
    int height; // in termini di "tile"
    int tile_w;
    int tile_h;

    vector<int> first_gids;

}
void level_loader::open_level(string path)
{
    using namespace configs;

    // es: "assets/foo.tmx"
    path = (string) "assets/" += path += ".tmx";

    // se la mappa è già stata caricata prima (un restart)
    if(path == doc_name) {
        reload = true;
        first_gids.resize(0);
        return;
    }
    // altrimenti imposta il non-ricaricamento
    reload = false;

    if(xmlDoc.LoadFile(path.c_str())
        != XML_SUCCESS)
            throw level_loader::opening_except{};
    doc_name = path;

    // il primo tag è <?xml...>, il secondo e ultimo è quello che a noi interessa invece.
    pRoot = xmlDoc.LastChild();
    assert_except<parse_except>(pRoot);

    XMLElement *pElement = pRoot->ToElement();
    assert_except<parse_except>(pRoot);
    pElement->QueryIntAttribute("tilewidth", &tile_w);
    pElement->QueryIntAttribute("tileheight", &tile_h);
    pElement->QueryIntAttribute("width", &width);
    pElement->QueryIntAttribute("height", &height);

    first_gids.resize(0);
}

void level_loader::load_map_properties(room_info &ri)
{
    if(configs::reload)
        return;
    // otteniamo prima il background, poi il titolo;
    // può sembrare strano, ma il fatto è che il titolo è una
    // proprietà personalizzata ed è salvato in un tag specializzato

    // formato background nel tag XML: "#RRGGBB"
    XMLElement *pElement = configs::pRoot->ToElement();
    string bg; Uint32 colour;
    bg = pElement->Attribute("backgroundcolor");

    colour = stoul(bg.c_str() + 1, 0, 16);
    ri.background.r = ((colour & 0xFF0000) >> 16);
    ri.background.g = ((colour & 0x00FF00) >> 8);
    ri.background.b = (colour & 0x0000FF);

    /* ordine dei tag:
     * <map ...>
     *  <properties>
     *   <property name="..." value="..."/>
     *   <property name="..." value="..."/>
     *   ...
     *  </properties>
     * */
    XMLElement *property = pElement->FirstChild()->FirstChildElement();
    for(; property != nullptr; property = property->NextSiblingElement())
    {
        if(strcmp((property->Attribute("name")), "title") == 0)
            ri.title = property->Attribute("value");
        if(strcmp((property->Attribute("name")), "BGM") == 0)
            ri.BGM_file = property->Attribute("value");
    }
    ri.level_dim.w = configs::width * configs::tile_w;
    ri.level_dim.h = configs::height * configs::tile_h;
}

void level_loader::parse_layer(std::vector<std::unique_ptr<tile_model>> &tile_layer)
{
    if(configs::reload)
        return;
    tile_layer.resize(0);
    // il tag tileset contiene le informazioni sui modelli (tileset).
    for(XMLElement *pElement = configs::pRoot->FirstChildElement("tileset");
        pElement != nullptr; pElement = pElement->NextSiblingElement("tileset"))
    {
        int gid;
        int t_w, t_h;
        pElement->QueryIntAttribute("firstgid", &gid);

        // aggiungi il gid corrispondente al tileset
        configs::first_gids.push_back(gid);

        // immetti le dimensioni del tileset
        pElement->QueryIntAttribute("tilewidth", &t_w);
        pElement->QueryIntAttribute("tileheight", &t_h);

        // il tag figlo è <image>, che contiene informazioni sul modello
        XMLElement *image_tag = pElement->FirstChildElement();

        // inizializza il modello
        string res_path = image_tag->Attribute("source");
        // toglie ".../"
        res_path = res_path.substr(3);
        tile_layer.emplace_back(new tile_model(res_path.c_str(), t_w, t_h));
    }
}

void level_loader::parse_tiles(std::vector<std::unique_ptr<tile_model>>& tilesets,
                               std::vector<std::unique_ptr<Tile>>& tiles)
{
    if(configs::reload)
        return;
    tiles.resize(0);
    using namespace configs;
    XMLElement *curLayer = configs::pRoot->FirstChildElement("layer");
    assert_except<parse_except>(curLayer);

    /* Qui i tag sono: <layer ...>
     *              <data>
     *               <tile gid="x"/>
     * */

    int x = 0, y = 0;
    for(XMLElement *cur_tile = curLayer->FirstChildElement()->FirstChildElement();
        cur_tile != nullptr; cur_tile = cur_tile->NextSiblingElement("tile"))
    {
        int read_gid;
        cur_tile->QueryIntAttribute("gid", &read_gid);

        // itera il vettore dalla fine verso l'inizio
        for(int i = first_gids.size() - 1;
            i >= 0; i--)
        {
            if(read_gid >= first_gids[i]) // se abbiamo trovato il gid adatto
                tiles.emplace_back(new Tile(read_gid - first_gids[i], *tilesets[i], x, y));
        }
        x += configs::tile_w;
        if(x >= width * configs::tile_w)
            x = 0, y += configs::tile_h;
    }
}

void level_loader::parse_objects(instance_container& ic, game_instance_generic** followed)
{
    /* Ordine dei tag:
     *          <objectgroup name="">
     *           <object id="" name="" x="" y="" width="" height="" .../>
     * */
    XMLElement *pObjectGroup = configs::pRoot->FirstChildElement("objectgroup");
    assert_except<parse_except>(pObjectGroup);

    for(XMLElement *pObject = pObjectGroup->FirstChildElement();
        pObject != nullptr; pObject = pObject->NextSiblingElement())
        recognize_types::recognize(pObject, ic, followed);
}

