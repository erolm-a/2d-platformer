#ifndef BAD_CLOUD_H
#define BAD_CLOUD_H

// bad_cloud: classe della nuvola cattiva (quella che toccata causa la morte del giocatore).
// Se è visibile ha l'aspetto di una normale nuvola, altrimenti è invisibile ma il
// comportamento è uguale

#include "game/game_instance_generic.h"

class bad_cloud : public game_instance_generic
{
public:
    void spawn(int x, int y) override;
    void handle_collision(game_instance_generic& other) override;
};

#endif // BAD_CLOUD_H
