#ifndef EVENT_H
#define EVENT_H

/*
 * La classe event: gestisce gli eventi.
 * Dato che è una classe condivisa da molti oggetti è una classe statica.
 * Quindi non avrebbe molto senso istanziare un oggetto event.
 * */

#include <SDL_events.h>

typedef Uint32 Event_Type;

enum class event_types : Event_Type {
    QUIT = SDL_QUIT,
    KEYDOWN = SDL_KEYDOWN,
    MOUSE_PRESSED = SDL_MOUSEBUTTONDOWN,
    MOUSE_RELEASED = SDL_MOUSEBUTTONUP,
    MOUSE_MOVEMENT = SDL_MOUSEMOTION
};

// non tutti i codici sono supportati.
namespace key_codes {
    //int num_supported_keys {43};
    using key_type = int;
    constexpr auto ESC = SDL_SCANCODE_ESCAPE;
    constexpr auto NUM_0 = SDL_SCANCODE_0;
    constexpr auto NUM_1 = SDL_SCANCODE_1;
    constexpr auto NUM_2 = SDL_SCANCODE_2;
    constexpr auto NUM_3 = SDL_SCANCODE_3;
    constexpr auto NUM_4 = SDL_SCANCODE_4;
    constexpr auto NUM_5 = SDL_SCANCODE_5;
    constexpr auto NUM_6 = SDL_SCANCODE_6;
    constexpr auto NUM_7 = SDL_SCANCODE_7;
    constexpr auto NUM_8 = SDL_SCANCODE_8;
    constexpr auto NUM_9 = SDL_SCANCODE_9;

    constexpr auto A = SDL_SCANCODE_A;
    constexpr auto B = SDL_SCANCODE_B;
    constexpr auto C = SDL_SCANCODE_C;
    constexpr auto D = SDL_SCANCODE_D;
    constexpr auto E = SDL_SCANCODE_E;
    constexpr auto F = SDL_SCANCODE_F;
    constexpr auto G = SDL_SCANCODE_G;
    constexpr auto H = SDL_SCANCODE_H;
    constexpr auto I = SDL_SCANCODE_I;
    constexpr auto J = SDL_SCANCODE_J;
    constexpr auto K = SDL_SCANCODE_K;
    constexpr auto L = SDL_SCANCODE_L;
    constexpr auto M = SDL_SCANCODE_M;
    constexpr auto N = SDL_SCANCODE_N;
    constexpr auto O = SDL_SCANCODE_O;
    constexpr auto P = SDL_SCANCODE_P;
    constexpr auto Q = SDL_SCANCODE_Q;
    constexpr auto R = SDL_SCANCODE_R;
    constexpr auto S = SDL_SCANCODE_S;
    constexpr auto T = SDL_SCANCODE_T;
    constexpr auto U = SDL_SCANCODE_U;
    constexpr auto V = SDL_SCANCODE_V;
    constexpr auto W = SDL_SCANCODE_W;
    constexpr auto X = SDL_SCANCODE_X;
    constexpr auto Y = SDL_SCANCODE_Y;
    constexpr auto Z = SDL_SCANCODE_Z;

    constexpr auto LSHIFT = SDL_SCANCODE_LSHIFT;

    constexpr auto DOWN = SDL_SCANCODE_DOWN;
    constexpr auto LEFT = SDL_SCANCODE_LEFT;
    constexpr auto RIGHT = SDL_SCANCODE_RIGHT;
    constexpr auto UP = SDL_SCANCODE_UP;
    constexpr auto SPACE = SDL_SCANCODE_SPACE;
}

namespace event {
    // aggiorna gli eventi
    int _update_ev();
    // ottieni il tipo di evento
    event_types get_type();
    // ottieni l'evento specifico
    SDL_Scancode get_key();
}

namespace keystate {
    const Uint8 *get_keystate(int *lenght = nullptr);
}

#endif // EVENT_H
