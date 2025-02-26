#include "arena.h"
#include <SDL2/SDL.h>

// Inicializacija arene
Arena arena;

void initArena(Arena &arena, int x, int y, int width, int height) {
    arena.x = x;
    arena.y = y;
    arena.width = width;
    arena.height = height;
    arena.complete = false;
    arena.exitActive = false;
    arena.exitPortalActive = false;
    arena.enemiesDefeated = 0;
}

// Risanje arene (vidne stene)
void drawArena(SDL_Renderer* renderer, const Arena &arena) {
    SDL_Rect rect = { arena.x, arena.y, arena.width, arena.height };
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);  // Rdeča arena
    SDL_RenderDrawRect(renderer, &rect);
}


// Posodobitev stanja arene
void updateArena() {
    // Ko so vsi sovražniki premagani, aktiviramo izhodna vrata
    if (arena.enemiesDefeated && !arena.exitPortalActive) {
        arena.exitPortalActive = true;
    }
}

// Preverjanje, ali je igralec dosegel izhod iz arene
bool checkArenaExit(Player* player) {
    if (arena.exitActive) {
        // Preveri, če je igralec na položaju vrat (prilagodimo kasneje, ko jih dodamo)
        return true; 
    }
    return false;
}
void checkArenaCollision(Player &player, const Arena &arena) {
    if (player.x < arena.x) player.x = arena.x;
    if (player.y < arena.y) player.y = arena.y;
    if (player.x + player.size > arena.x + arena.width) player.x = arena.x + arena.width - player.size;
    if (player.y + player.size > arena.y + arena.height) player.y = arena.y + arena.height - player.size;
}