#include "arena.h"
#include <SDL2/SDL.h>

Arena arena;

void initArena(Arena &arena, int x, int y, int width, int height) {
    arena.x = x;
    arena.y = y;
    arena.width = width;
    arena.height = height;
    arena.exitPortalActive = false;
    arena.complete = false;
    arena.exitActive = false;
    arena.enemiesDefeated = 0;
    arena.animalsRescued = 0;  // 🔹 Inicializacija rešenih živali
}

void drawArena(SDL_Renderer* renderer, const Arena &arena) {
    SDL_Rect rect = { arena.x, arena.y, arena.width, arena.height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
}

void updateArena(Arena &arena) {
    if (arena.animalsRescued >= 3) {  // 🔹 Ko igralec reši 3 živali, se aktivira izhod
        arena.exitActive = true;
    }
}

void checkArenaCollision(Player &player, const Arena &arena) {
    // Logika za preverjanje trkov igralca z areno
}

void rescueAnimal(Arena &arena) {
    arena.animalsRescued++;
}
