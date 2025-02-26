#include "portal.h"
#include <SDL2/SDL.h>
#include "arena.h"
extern Arena arena;


void initPortal(Portal &portal, int x, int y) {
    portal.x = x;
    portal.y = y;
    portal.size = 50;
    portal.active = true;
    portal.activationTime = 0;
    portal.lastSpawnTime = 0; // Inicializiramo spremenljivko
    portal.timer = 0;         // Inicializiramo spremenljivko
}

void updatePortal(Portal &portal, Uint32 currentTime) {
    if (!portal.active && (currentTime - portal.lastSpawnTime > 5000)) {
        portal.active = true;
        portal.lastSpawnTime = currentTime;
        portal.timer = currentTime;  
    }

    if (!portal.active && (currentTime - portal.lastSpawnTime > 5000)) {
        portal.active = true;
        portal.lastSpawnTime = currentTime; // Posodobimo čas zadnje aktivacije
    }
}


void checkPortalCollision(Player* player, Portal &portal, Uint32 currentTime) {
    if (!portal.active) return;

    SDL_Rect playerRect = { static_cast<int>(player->x), static_cast<int>(player->y), player->size, player->size };
    SDL_Rect portalRect = { portal.x, portal.y, portal.size, portal.size };

    if (SDL_HasIntersection(&playerRect, &portalRect)) {
        // Ko igralec stopi v portal, ga teleportiramo v areno
        vAreni = true;  // Označimo, da je v areni
        player->x = 500;  // Nova začetna lokacija v areni
        player->y = 500;
        initArena(arena, 450, 450, 300, 200);  // Postavimo areno nekam drugam
    }
}


void drawPortal(SDL_Renderer* renderer, Portal &portal, Uint32 currentTime) {
    if (!portal.active) return;

    // Spreminjanje barve vsakih 300 ms, temelji na času portala
    int alpha = ((currentTime - portal.timer) / 300 % 2) ? 255 : 100;

    SDL_SetRenderDrawColor(renderer, 150, 0, 255, 255);
    SDL_Rect rect = { portal.x, portal.y, portal.size, portal.size };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, alpha);
    SDL_RenderDrawRect(renderer, &rect);
}

void teleportPlayer(Player &player) {
    player.x = 500;  // Nastavi na novo lokacijo (prilagodi po želji)
    player.y = 500;
}