#include "vrata.h"
#include <SDL2/SDL.h>
#include "arena.h"

void initVrata(Vrata &vrata, int x, int y) {
    vrata.x = x;
    vrata.y = y;
    vrata.size = 50; // Velikost vrat
    vrata.active = false;
    vrata.activationTime = 0;
}

void updateVrata(Vrata &vrata, Uint32 currentTime, Arena &arena) {
    if (!vrata.active && arena.exitPortalActive) {
        vrata.active = true;
        vrata.activationTime = currentTime;
    }
    // Vrata ostanejo aktivna, dokler jih igralec ne uporabi
}

void drawVrata(SDL_Renderer* renderer, Vrata &vrata, Uint32 currentTime) {
    if (!vrata.active) return;
    
    // Barve vrat
    SDL_SetRenderDrawColor(renderer, 150, 0, 255, 255);
    SDL_Rect rect = { vrata.x, vrata.y, vrata.size, vrata.size };
    SDL_RenderFillRect(renderer, &rect);
    
    // Utripajoča bela obroba
    int alpha = (SDL_GetTicks() / 300 % 2) ? 255 : 100;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_RenderDrawRect(renderer, &rect);
}

bool checkVrataCollision(Player* player, Vrata &vrata) {
    if (!vrata.active) return false;
    
    SDL_Rect playerRect = { static_cast<int>(player->x), static_cast<int>(player->y), player->size, player->size };
    SDL_Rect vrataRect = { vrata.x, vrata.y, vrata.size, vrata.size };
    
    return SDL_HasIntersection(&playerRect, &vrataRect);
}