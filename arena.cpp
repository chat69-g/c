#include "arena.h"
#include <SDL2/SDL.h>

void drawArena(SDL_Renderer* renderer, const Arena& arena) {
    // Nastavimo črno ozadje
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Nastavimo sivo barvo za stene
    SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
    
    // Debelina zidov
    int zid = 20;

    // Zgornji zid
    SDL_Rect zgoraj = {0, 0, arena.width, zid};
    SDL_RenderFillRect(renderer, &zgoraj);

    // Spodnji zid
    SDL_Rect spodaj = {0, arena.height - zid, arena.width, zid};
    SDL_RenderFillRect(renderer, &spodaj);

    // Levi zid
    SDL_Rect levo = {0, 0, zid, arena.height};
    SDL_RenderFillRect(renderer, &levo);

    // Desni zid
    SDL_Rect desno = {arena.width - zid, 0, zid, arena.height};
    SDL_RenderFillRect(renderer, &desno);
}

// Preverimo, ali je igralec zadel zid
void checkArenaCollision(Player &player, const Arena &arena) {
    int zid = 20;

    // Preprečimo igralcu, da zapusti areno
    if (player.x < zid) player.x = zid;
    if (player.y < zid) player.y = zid;
    if (player.x + player.size > arena.width - zid) player.x = arena.width - zid - player.size;
    if (player.y + player.size > arena.height - zid) player.y = arena.height - zid - player.size;
}