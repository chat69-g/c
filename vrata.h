#ifndef VRATA_H
#define VRATA_H

#include <SDL2/SDL.h>
#include "igralec.h"
#include "arena.h"

struct Vrata {
    int x, y, size;
    bool active;
    Uint32 activationTime;
};

void initVrata(Vrata &vrata, int x, int y);
void updateVrata(Vrata &vrata, Uint32 currentTime, Arena &arena);
void drawVrata(SDL_Renderer* renderer, Vrata &vrata, Uint32 currentTime);
bool checkVrataCollision(Player* player, Vrata &vrata);

#endif
