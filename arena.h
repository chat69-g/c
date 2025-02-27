#ifndef ARENA_H
#define ARENA_H

#include <SDL2/SDL.h>
#include "igralec.h"

struct Arena {
    int x, y, width, height;
    bool exitPortalActive;
    bool complete;
    bool exitActive;
    int enemiesDefeated;
    int animalsRescued;
};


void initArena(Arena &arena, int x, int y, int width, int height);
void drawArena(SDL_Renderer* renderer, const Arena& arena);
extern Arena arena; // Tukaj samo DEKLARACIJA
void updateArena(Arena &arena);
void checkArenaCollision(Player &player, const Arena &arena);
void rescueAnimal(Arena &arena);

#endif
