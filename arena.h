#ifndef ARENA_H
#define ARENA_H

#include <SDL2/SDL.h>
#include "igralec.h"

struct Arena {
    int x, y, width, height;
    bool exitPortalActive;
    bool complete;
    bool exitActive;
    int enemiesDefeated;  // Dodano polje
};

extern Arena arena;  // 🔹 Samo deklaracija

void initArena(Arena &arena, int x, int y, int width, int height);
void drawArena(SDL_Renderer* renderer, const Arena &arena);
void updateArena(Arena &arena);
void checkArenaCollision(Player &player, const Arena &arena);
void drawExitPortal(SDL_Renderer* renderer, const Arena &arena);
bool checkExitPortalCollision(const Player &player, const Arena &arena);

#endif