#ifndef IGRALEC_H
#define IGRALEC_H

#include <SDL2/SDL.h>

struct Player {
    float x, y;
    int size;
    float speed;
};

void handleInput();
void updatePlayer();
void drawPlayer(SDL_Renderer* renderer);

extern Player player;
extern bool vAreni; // Tukaj samo DEKLARACIJA, ne definicija

#endif
